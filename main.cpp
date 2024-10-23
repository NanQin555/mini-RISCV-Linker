#include "args.hpp"
#include "Input.hpp"
string version = string(VERSION) + "-" + COMMIT_ID;
int main(int argc, char* argv[]) {
    if(argc<2) {
        assert(0&&"params number error");
    }
    Context ctx = Context();
    vector<string> remaining = parseArgs(argc, argv, ctx);
    if (ctx.Args.Emulation==MachineType::None) {
        for(auto filename: remaining) {
            if (filename.substr(0,1)=="-")
                continue;
            ObjectFile file(&ctx, filename);
            ctx.Args.Emulation = GetMachineTypeFromContents(file.file->contents);
            if (ctx.Args.Emulation !=MachineType::None)
                break;
        }
    }
    assert(ctx.Args.Emulation == MachineType::RISCV64 && "unknown emulation type");
    for(auto x: remaining) {
        cout << x << endl;
    }
    ReadInputFiles(&ctx, remaining);
    
    cout << "Not IsAlive : " << endl;
    for(auto obj: ctx.Objs) {
        if(obj->IsAlive)
            cout << obj->file->name << endl;
    }
    
    return 0;
}