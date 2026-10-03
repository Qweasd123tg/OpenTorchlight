// Raw CALLIND engine calibration. RAM is an explicit fixture; game objects and
// application policies are not reconstructed by this executable.
#include "torchlight/lifted_address_space.hpp"
#include "torchlight/generated/indirect_machine.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {
using torchlight::pcode::AddressSpace;
constexpr std::uint64_t sentinel = 0x7ff00000, stack = 0x80000;
constexpr std::uint64_t owner = 0x10010, list = 0x30010, object = 0x50010;
constexpr std::uint64_t count = 0x70010, global = 0x142c4a0;
void put(std::vector<std::uint8_t>& data, std::size_t offset, std::size_t width, std::uint64_t value) {
    for (std::size_t n=0;n<width;++n) data.at(offset+n)=static_cast<std::uint8_t>(value>>(8*n));
}
void unchanged(AddressSpace& ram, std::uint64_t base, const std::vector<std::uint8_t>& data) {
    for (std::size_t n=0;n<data.size();++n)
        if (ram.read(base+n,1)!=data[n]) throw std::runtime_error("unexpected fixture mutation");
}
struct Table { std::uint64_t address; std::vector<std::uint8_t> bytes; };
std::vector<Table> tables(const char* path) {
    std::ifstream input(path);
    if (!input) throw std::runtime_error("cannot read source vtable fixture");
    std::vector<Table> result;
    std::uint64_t address; std::string hex;
    while (input>>std::hex>>address>>hex) {
        if (hex.size()%2) throw std::runtime_error("odd vtable byte encoding");
        std::vector<std::uint8_t> bytes;
        for (std::size_t n=0;n<hex.size();n+=2)
            bytes.push_back(static_cast<std::uint8_t>(std::stoul(hex.substr(n,2),nullptr,16)));
        result.push_back({address,std::move(bytes)});
    }
    return result;
}
}
int main(int argc,char** argv) { try {
    if (argc!=2) throw std::runtime_error("expected read-only source tables");
    const auto source_tables=tables(argv[1]);
    std::string command;
    while (std::cin>>command) {
        AddressSpace ram({65536,1048576,96});
        for (const auto& table:source_tables) ram.map_snapshot(table.address,table.bytes);
        ram.allocate(stack,256,AddressSpace::Initialization::unknown);
        ram.write(stack+192,8,sentinel);
        torchlight::pcode::RegisterFile regs;
        regs.write(0x20,8,stack+192);
        const std::size_t saved[]={0x18,0x28,0xa0,0xa8,0xb0,0xb8};
        for (auto offset:saved) regs.write(offset,8,0xcafe0000+offset);
        if (command=="p") {
            std::size_t size; if (!(std::cin>>size)||size>40) throw std::runtime_error("invalid list fixture");
            std::vector<std::uint8_t> ui(0x1960,0xa7), vector(size*8+32,0xa7);
            put(ui,16+0x1930,8,list);put(ui,16+0x1938,8,list+size*8);
            for (std::size_t n=0;n<size;++n) {
                unsigned kind,flag;
                if (!(std::cin>>kind>>flag)||kind>1||flag>255) throw std::runtime_error("invalid menu fixture");
                const auto base=object+n*0x1000;
                std::vector<std::uint8_t> bytes(0x220,0xa7);
                put(bytes,16,8,kind?0xff0e30:0xfe6270);
                put(bytes,16+(kind?0x188:0x98),1,flag);
                ram.map_snapshot(base-16,bytes);
                put(vector,16+n*8,8,base);
            }
            ram.map_snapshot(owner-16,ui);ram.map_snapshot(list-16,vector);
            regs.write(0x38,8,owner);
            torchlight::pcode_machine::fn_00a82ae0(ram,regs,sentinel);
            unchanged(ram,owner-16,ui);unchanged(ram,list-16,vector);
            for (auto offset:saved)
                if (regs.read(offset,8)!=0xcafe0000+offset) throw std::runtime_error("callee-saved state differs");
            std::cout<<regs.read(0,8)<<'\n';
        } else if (command=="e") {
            unsigned present,flag;std::uint32_t initial_count,initial_global;
            if (!(std::cin>>present>>flag>>initial_count>>initial_global)||present>1||flag>255)
                throw std::runtime_error("invalid descriptor fixture");
            std::vector<std::uint8_t> bytes(0x220,0xa7);
            put(bytes,16,8,0xfd8e50);put(bytes,16+0x82,1,flag);
            ram.map_snapshot(object-16,bytes);
            std::vector<std::uint8_t> counter(36,0xa7), result(36,0xa7);
            put(counter,16,4,initial_count);put(result,16,4,initial_global);
            ram.map_snapshot(count-16,counter,true);
            ram.map_snapshot(global-16,result,true);
            regs.write(0x38,8,present?object:0);
            // Null path deliberately has no RSI; source must not read it.
            if (present) regs.write(0x30,8,count);
            torchlight::pcode_machine::fn_005bb4a0(ram,regs,sentinel);
            unchanged(ram,object-16,bytes);
            if (present) { put(counter,16,4,1);put(result,16,1,flag); }
            unchanged(ram,count-16,counter);unchanged(ram,global-16,result);
            std::cout<<regs.read(0,8)<<' '<<ram.read(count,4)<<' '<<ram.read(global,4)<<'\n';
        } else throw std::runtime_error("unknown engine fixture");
        if (regs.read(0x20,8)!=stack+200||regs.read(0x288,8)!=sentinel)
            throw std::runtime_error("CALLIND/RET stack state differs");
        for (const auto& table:source_tables) unchanged(ram,table.address,table.bytes);
    }
    return 0;
} catch (const torchlight::pcode::UntranslatedCallTarget& error) {
    // Observed guest address only. The collector verifies the exact source
    // body before adding it; this observation does not authorize guest replay.
    std::cerr<<"{\"schema\":1,\"kind\":\"observed-machine-call-targets\","
        "\"original_elf_sha256\":\"91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b\","
        "\"targets\":[\"0x"<<std::hex<<error.target<<"\"]}\n";
    return 2;
} catch (const std::exception& error) { std::cerr<<error.what()<<'\n';return 1; } }
