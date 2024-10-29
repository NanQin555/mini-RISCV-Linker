#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "context.hpp"
using namespace std;
extern string version;
#ifdef DEBUG
void printArgs(int argc, char* argv[]) {
    cout << "Args list: " << endl;
    for(int i=0; i<argc; i++)
        cout << argv[i] << endl;
    cout << endl;
}
#endif

vector<string> parseArgs(int argc, char* argv[], Context& ctx) {
#ifdef DEBUG
    printArgs(argc, argv);
#endif
    vector<string> args;
    vector<string> remaining;
    string arg;
    for(int i=1; i<argc; i++) {
        string arg = argv[i];
        args.push_back(arg);
    }
    auto dashes = [&](string name) {
        vector<string> param;
        if (name.size()==1) {
            param.emplace_back(string("-"+name));
            return param;
        }
        else {
            param.emplace_back(string("-"+name));
            param.emplace_back(string("--"+name));
            param.emplace_back(string(name));
            return param;
        }
    };
    auto readFlag = [&](string name) {
        for(auto opt: dashes(name)) {
            if(args[0]==opt) {
                args.assign(args.begin()+1, args.end());
                return true;
            }
        }
        return false;
    };
    auto readArg = [&](string name) {
        for(auto opt: dashes(name)) {
            if(args[0]==opt) {
                if(args.size()==1) {
                    assert(0&&("option - argument miss"));
                }
                arg = args[1];
                args.assign(args.begin()+2, args.end());
                return true;
            }
            string prefix = opt;
            if (name.size()>1)
                prefix += "=";
            if (prefix == args[0].substr(0, prefix.size())) {
                arg = args[0].substr(prefix.size());
                args.assign(args.begin()+1, args.end());
                return true;
            }
        }
        return false;
    };

    while(args.size()>0) {
        if (readFlag("h")||readFlag("help")) {
            cout << "usage: " << args[0] << "[options] file...\n" << endl;
            exit(0);
        }
        if (readFlag("v")||readFlag("version")) {
            cout << "rvld version: " << version << endl;
            exit(0);
        }
        if (readArg("o") || readArg("output")) {
            ctx.Args.Output = arg;
        } 
        else if (readArg("m")) {
            if (arg == "elf64lriscv") {
                ctx.Args.Emulation = MachineType::RISCV64;
            }
            else assert(0&&"Unknown -m argument");
        }
        else if (readArg("L")) {
            ctx.Args.LibraryPaths.push_back(arg);
        }
        else if (readArg("l")) {
            remaining.push_back("-l"+arg);
        }
        else if (readArg("sysroot") || 
                readFlag("static") || 
                readArg("plugin") || 
                readArg("plugin-opt") || 
                readFlag("as-needed") ||
                readFlag("start-group") || 
                readFlag("end-group") || 
                readArg("hash-style") ||
                readArg("build-id") || 
                readFlag("s") ||
                readFlag("no-relax") ||
                readFlag("z") ||
                readFlag("relro")) {
            // ignored
        }
        else {
            assert(args[0] != "-"&&"unknow command line option");
            remaining.push_back(args[0]);
            args.assign(args.begin()+1,args.end());
        }
    }

    return remaining;
}