#pragma once
#include "ObjectFile.hpp"
#include "filetype.hpp"
#include  "context.hpp"
#include "archive.hpp"
using namespace std;

ObjectFile* CreateObjectFile(Context* ctx, File* file, bool inLib) {
    // CheckFileCompatibility(ctx, file);
    return new ObjectFile(file, !inLib);
}

void ReadFile(Context* ctx, File* file) {
    FileType fy = GetFileType(file->contents);
    if(fy == FileType::FileTypeObject) {
        ctx->Objs.emplace_back(new ObjectFile(file->name));
    }
    else if(fy == FileType::FileTypeArchive) {
        for(auto archivefile: ReadArchiveMembers(file)) {
            assert(GetFileType(archivefile->contents)==FileType::FileTypeObject);
            ctx->Objs.push_back(CreateObjectFile(ctx, archivefile, true));
        }
    }
    else {
        assert(0&&"unknown file type");
    }
}

void ReadInputFiles(Context* ctx, vector<string> remaining) {
    for(auto str: remaining) {
        if(RemovePrefix(str, "-l")) {
            ReadFile(ctx, FindLibrary(ctx, str));
        }
        else {
            ReadFile(ctx, new File(str));
        }
    }
} 


