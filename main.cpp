#include "args.hpp"
#include "Input.hpp"
#include "passes.hpp"
string version = string(VERSION) + "-" + COMMIT_ID;
int main(int argc, char* argv[]) {
    if(argc<2) {
        assert(0&&"params number error");
    }
    Context ctx = Context();
    passes pass;
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
    pass.ResolveSymbols(&ctx);

    cout << "Test: ";
    for (auto obj: ctx.Objs) {
        if(obj->file->name=="out/object/test.o") {
            for(auto sym: obj->Symbols) {
                if(sym->Name=="puts") {
                    cout << sym->File->file->parent->name << endl;
                }
            }
        }
    }

    
    return 0;
}  