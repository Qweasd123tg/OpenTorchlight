import sys,tempfile,pathlib,threading,json
root=pathlib.Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/dot-all-work-2026-10-05/OpenTorchlight/source')
sys.path.insert(0,str(root/'tools/decomp'))
import parallel as p
with tempfile.TemporaryDirectory(prefix='otl-claim-proof-') as folder:
 p.ROOT=pathlib.Path(folder);p.CLAIMS=p.ROOT/'build-decomp/claims.json';p.OWNERS=p.ROOT/'owners.json'
 db={'functions':{'0x1':{'kind':'function','tu':1,'size':100,'scope':''}},'tus':[{'id':1,'name':'Only.cpp','kind':'game'}],'classes':{}}
 p.elfdb.load_db=lambda:db
 # Hold both threads immediately before saving, after they selected work and read the ledger.
 barrier=threading.Barrier(2);lock=threading.Lock();save=p.save_claims;made=[];errors=[]
 def synced_save(data):
  barrier.wait(timeout=5)
  with lock:save(data) # Serial writes exclude torn JSON as a confounder.
 p.save_claims=synced_save
 p.new=lambda slug,tus:made.append({'worker':slug,'tus':list(tus)})
 def worker(slug):
  try:p.claim(slug,1000)
  except Exception as e:errors.append(str(e))
 threads=[threading.Thread(target=worker,args=(n,)) for n in ('worker-a','worker-b')]
 for t in threads:t.start()
 for t in threads:t.join()
 concurrent={'created':made,'ledger':p.claims(),'errors':errors}
 assert len(made)==2 and made[0]['tus']==made[1]['tus']==['Only.cpp'] and len(p.claims())==1 and not errors
 # Independent failure case: recording a claim precedes worktree creation.
 p.save_claims=save;save({})
 def fail_new(slug,tus):raise RuntimeError('synthetic worktree creation failure')
 p.new=fail_new
 try:p.claim('failed-worker',1000)
 except RuntimeError:pass
 failed={'ledger':p.claims(),'remaining_candidates':p.candidates(db)}
 assert failed['ledger']=={'failed-worker':['Only.cpp']} and not failed['remaining_candidates']
 result={'scope':'Actual parallel.claim/candidates/save_claims with synthetic DB, temporary root and new() stub. No real worktrees, compilation or game touched.','concurrent':concurrent,'creation_failure':failed}
 print('RESULT='+json.dumps(result))
