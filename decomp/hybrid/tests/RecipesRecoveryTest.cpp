#include <malloc.h>
#include "tests/NativeGameServices.h"
#include "SystemsFixtureWorker.h"
#include "DataGroup.h"
#include "FileSystem.h"
#include "Hierarchy.h"
#include "Recipe.h"
#include "Recipes.h"
#include "SafePointer.h"
#include "StringUtilities.h"

TL_ORIGINAL(void, recipesOldLoad, (CRecipe*, CDataGroup*), "_ZN7CRecipe4loadEP10CDataGroup")
TL_ORIGINAL(void, recipesOldReload, (CRecipes*), "_ZN8CRecipes6reloadEv")
TL_ORIGINAL(void, recipesOldDtor, (CRecipes*), "_ZN8CRecipesD1Ev")
extern "C" void recipesNewLoad(CRecipe*, CDataGroup*) __asm__("_ZN7CRecipe4loadEP10CDataGroup");
extern "C" void recipesNewReload(CRecipes*) __asm__("_ZN8CRecipes6reloadEv");
extern "C" void recipesNewDtor(CRecipes*) __asm__("_ZN8CRecipesD1Ev");
extern "C" void* nativeRecipesSingleton __asm__("_ZL10g_pRecipes");
extern "C" char recipesVtable[] __asm__("_ZTV8CRecipes");

namespace {
struct Case { unsigned index, operation; bool negative; };
template<class T> union Storage { long double alignment; unsigned char bytes[sizeof(T)]; };
TArrayList<std::wstring>* files;
std::wstring* gamePath;
std::vector<std::wstring>* typeNames;
unsigned operation;

void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }
std::wstring decimal(unsigned i) { return STRINGS::GetValueAsWString(i); }

void buildGroup(CDataGroup& group, unsigned seed)
{
    const unsigned counts[] = {0, 1, 3, 11, 24, 2};
    unsigned ingredients = counts[seed % 6], results = counts[(seed / 6) % 6];
    group.AddDataGroup(L"OTHER")->AddDataValue(L"UNIT", L"ignored", false);
    for (unsigned i = 0; i < ingredients; ++i) {
        CDataGroup* child = group.AddDataGroup(L"INGREDIENT");
        if ((seed + i) % 4) child->AddDataValue(L"UNIT", (L"unit/\x0416" + decimal(i)).c_str(), false);
        unsigned mode = (seed + i) % 6;
        std::wstring type;
        if (mode == 2) type = L"MISSING_RECIPE_TYPE";
        else if (mode == 3) type = (*typeNames)[(seed + i) % typeNames->size()];
        else if (mode == 4) type = STRINGS::StringLower((*typeNames)[(seed + i) % typeNames->size()]);
        else if (mode == 5) type = L"\x0422\x0418\x041f";
        if (mode) child->AddDataValue(L"UNITTYPE", type.c_str(), false);
        if ((seed + i) % 3) {
            const int countValues[] = {-7, 0, 1, 3, 1000000};
            child->AddDataValue(L"COUNT", countValues[(seed + i) % 5]);
        }
    }
    for (unsigned i = 0; i < results; ++i) {
        CDataGroup* child = group.AddDataGroup(L"RESULT");
        if ((seed + i) % 3) child->AddDataValue(L"UNIT", (L"result/" + decimal(i)).c_str(), false);
        if ((seed + i) % 4) child->AddDataValue(L"SPAWNCLASS", (L"spawn/\x0416" + decimal(i)).c_str(), false);
    }
}

void fillGroup(CDataGroup& group, unsigned seed)
{
    if (seed >= 36) group.LoadFile((*files)[(seed - 36) % files->size()], NULL);
    else buildGroup(group, seed);
}

template<class T> void captureList(autotest::Capture& out, const TArrayList<T>& list)
{
    unsigned values[3];
    std::memcpy(values, reinterpret_cast<const char*>(&list) + 8, sizeof(values));
    out.add(values, sizeof(values));
}

void captureRecipe(autotest::Capture& out, CRecipe* recipe)
{
    number(out, recipe != NULL);
    if (!recipe) return;
    captureList(out, recipe->m_inputs);
    for (unsigned i = 0; i < recipe->m_inputs.size(); ++i) {
        RecipeInput* input = recipe->m_inputs[i];
        number(out, input != NULL);
        if (input) {
            number(out, input->m_type);
            number(out, input->m_count);
            out.addText(input->m_unit);
        }
    }
    captureList(out, recipe->m_outputs);
    for (unsigned i = 0; i < recipe->m_outputs.size(); ++i) {
        RecipeOutput* output = recipe->m_outputs[i];
        number(out, output != NULL);
        if (output) { out.addText(output->m_unit); out.addText(output->m_spawnClass); }
    }
}

void prefill(CRecipe* recipe, unsigned seed, std::vector<std::wstring>& strings)
{
    for (unsigned i = 0; i < seed % 5; ++i) {
        if ((seed + i) % 4 == 0) { recipe->m_inputs.add(NULL); recipe->m_outputs.add(NULL); continue; }
        strings.push_back(std::wstring(80 + i, wchar_t(L'A' + i)));
        RecipeInput* input = new RecipeInput;
        input->m_type = static_cast<UNITTYPES::EUNITTYPES>(i + 3);
        input->m_count = int(i) - 2;
        input->m_unit = strings.back();
        recipe->m_inputs.add(input);
        RecipeOutput* output = new RecipeOutput;
        output->m_spawnClass = strings.back();
        output->m_unit = strings.back();
        recipe->m_outputs.add(output);
    }
}

void captureStrings(autotest::Capture& out, std::vector<std::wstring>& strings)
{
    for (unsigned i = 0; i < strings.size(); ++i) {
        int refcount;
        std::memcpy(&refcount, reinterpret_cast<const char*>(strings[i].data()) - 8, sizeof(refcount));
        number(out, refcount);
        out.addText(strings[i]);
    }
}

CRecipes* makeOwner(Storage<CRecipes>& storage, unsigned seed, std::vector<std::wstring>& strings)
{
    CRecipes* owner = reinterpret_cast<CRecipes*>(storage.bytes);
    new (static_cast<CRunicCore*>(owner)) CRunicCore;
    const wchar_t* paths[] = {gamePath->c_str(), L"", L"media/no_such_recipes/", L"MEDIA/RECIPES/"};
    new (&owner->m_sPath) std::wstring(paths[seed % 4]);
    new (&owner->m_recipes) TArrayList<CRecipe*>(3);
    const void* table = recipesVtable + 16;
    std::memcpy(owner, &table, sizeof(table));
    for (unsigned i = 0; i < (seed / 4) % 5; ++i) {
        if ((seed + i) % 5 == 0) { owner->m_recipes.add(NULL); continue; }
        CRecipe* recipe = new CRecipe;
        prefill(recipe, seed + i, strings);
        owner->m_recipes.add(recipe);
    }
    return owner;
}

void side(void* raw, bool ours, autotest::Capture& out)
{
    Case& c = *static_cast<Case*>(raw);
    std::vector<std::wstring> strings;
    strings.reserve(128);
    if (c.operation == 0) {
        CDataGroup group(L"RECIPE", NULL, 20, 10, NULL);
        fillGroup(group, c.index);
        CRecipe* recipe = new CRecipe;
        std::memset(recipe->m_unknown0, 0x5a, sizeof(recipe->m_unknown0));
        prefill(recipe, c.index, strings);
        typedef void (*Function)(CRecipe*, CDataGroup*);
        Function function = ours ? recipesNewLoad : recipesOldLoad;
        if (!autotest::beginInvocation(out, function)) return;
        function(recipe, &group);
        out.callCompleted = 1;
        if (ours && c.negative) recipe->m_inputs.add(NULL);
        captureRecipe(out, recipe);
        out.add(recipe->m_unknown0, sizeof(recipe->m_unknown0));
        delete recipe;
    } else {
        Storage<CRecipes> storage;
        CRecipes* owner = makeOwner(storage, c.index, strings);
        TSafePointer<CRunicCore> self;
        self.setObject(owner);
        int other = 0;
        nativeRecipesSingleton = c.index % 3 == 0 ? NULL : c.index % 3 == 1 ? static_cast<void*>(owner) : &other;
        void* previous = nativeRecipesSingleton;
        typedef void (*Function)(CRecipes*);
        Function function = c.operation == 1 ? (ours ? recipesNewReload : recipesOldReload) :
            (ours ? recipesNewDtor : recipesOldDtor);
        if (!autotest::beginInvocation(out, function)) return;
        function(owner);
        out.callCompleted = 1;
        if (c.operation == 1) {
            if (ours && c.negative) owner->m_recipes.add(NULL);
            number(out, nativeRecipesSingleton == previous);
            number(out, self.getObject() == owner);
            out.addText(owner->m_sPath);
            captureList(out, owner->m_recipes);
            for (unsigned i = 0; i < owner->m_recipes.size(); ++i) captureRecipe(out, owner->m_recipes[i]);
            recipesOldDtor(owner);
        } else {
            if (ours && c.negative) nativeRecipesSingleton = owner;
            number(out, nativeRecipesSingleton == NULL);
            number(out, self.getObject() == NULL);
        }
    }
    captureStrings(out, strings);
    malloc_trim(0);
    out.addHeapInUse();
}
void before(void* c, autotest::Capture& out) { side(c, false, out); }
void after(void* c, autotest::Capture& out) { side(c, true, out); }

int worker(const tlhybrid_host* host)
{
    nativegame::Services services;
    if (!services.ready()) return 1;
    CRecipes* gameRecipes = static_cast<CRecipes*>(nativeRecipesSingleton);
    if (!gameRecipes) return 1;
    gamePath = new std::wstring(gameRecipes->m_sPath);
    files = new TArrayList<std::wstring>(10);
    CFileSystem::getSingleton()->getFileList(*gamePath, *files, L"*.dat", true, true, false, false);
    typeNames = new std::vector<std::wstring>;
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    for (std::map<std::wstring, unsigned int>::iterator i = hierarchy->m_typeIDs.begin();
         i != hierarchy->m_typeIDs.end(); ++i) typeNames->push_back(i->first);
    host->log("    recipes fixture files %u native recipes %u hierarchy types %u\n",
        files->size(), gameRecipes->m_recipes.size(), unsigned(typeNames->size()));
    if (!files->size() || typeNames->empty()) return 1;
    // Populate lazy resource/type and repository state before differential forks.
    for (unsigned i = 0; i < 48; ++i) {
        CDataGroup group(L"RECIPE", NULL, 20, 10, NULL);
        fillGroup(group, i);
        CRecipe recipe;
        recipesOldLoad(&recipe, &group);
    }
    const char* names[] = {"recipes_recovery_load", "recipes_recovery_reload", "recipes_recovery_dtor"};
    const uintptr_t addresses[] = {0xe079c0, 0xe08280, 0xe075c0};
    autotest::Coverage coverage(names[operation], addresses[operation]);
    int failures = 0;
    for (unsigned i = 0; i < 48; ++i) {
        Case c = {i, operation, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    recipes seed%u op%u status%d/%d issue%u/%u bytes%lu/%lu\n", i,
                operation, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue,
                (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            for (size_t j = 0; j < a.capture.length && j < b.capture.length; ++j)
                if (a.capture.data[j] != b.capture.data[j]) {
                    host->log("    first difference %lu: %u/%u\n", (unsigned long)j,
                        unsigned(static_cast<unsigned char>(a.capture.data[j])),
                        unsigned(static_cast<unsigned char>(b.capture.data[j])));
                    break;
                }
            ++failures;
            break;
        }
    }
    coverage.report(host);
    Case negative = {7, operation, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &negative, a, 2000, 10000);
    autotest::runChild(after, &negative, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length ||
        std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    TL_CHECK(failures, detected && !autotest::incomplete(a) && !autotest::incomplete(b) &&
        a.reportValid && b.reportValid && !a.childStatus && !b.childStatus);
    host->log("    recipes negative control op%u detected %u complete %u/%u\n", operation,
        detected ? 1u : 0u, autotest::incomplete(a) ? 0u : 1u, autotest::incomplete(b) ? 0u : 1u);
    nativeRecipesSingleton = gameRecipes;
    delete files;
    delete gamePath;
    delete typeNames;
    return failures + (coverage.completed != 48);
}
}

TL_TEST(recipes_recovery_load) { operation = 0; return systems_fixture::isolated(worker, host); }
TL_TEST(recipes_recovery_reload) { operation = 1; return systems_fixture::isolated(worker, host); }
TL_TEST(recipes_recovery_dtor) { operation = 2; return systems_fixture::isolated(worker, host); }
