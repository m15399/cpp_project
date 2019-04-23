#include "main.h"

#include <dlfcn.h>

static int CompileCpp(const char* filename, const char* libname){
    char command[4096];
    snprintf(command, sizeof(command), "c++ %s -shared -o %s -fPIC", filename, libname);
    int r = system(command);
    return r;
}

static void* LoadLibrary(const char* libname){
    void* lib = dlopen(libname, RTLD_NOW | RTLD_GLOBAL);
    return lib;
}

static int CloseLibrary(void* lib){
   return dlclose(lib); 
}

static void PrintLibraryErrors(){
    cout << "dlerror: " << dlerror() << "\n";
}

int ExecuteCpp(const char* text){
    const char* filename = "/tmp/cpp.cpp";
    const char* libname = "/tmp/cpp.so";
    int r = 0;
    void* lib = nullptr;

    ssize_t bytesWritten = WriteToFile(filename, text);
    assert(bytesWritten >= 0);

    r = CompileCpp(filename, libname);

    if (r == 0){
        lib = LoadLibrary(libname);
        if (!lib){
            cout << "Failed to load library: " << libname << "\n";
            PrintLibraryErrors();
            r = 1;
        }
    }

    if (r == 0){
        const char* entryPointName = "rrr";
        int (*func)();
        *(void **)(&func) = dlsym(lib, entryPointName);
        if (func == nullptr){
            r = 1;
            cout << "Failed to find symbol: " << entryPointName << "\n";
            PrintLibraryErrors();
        }

        if (r == 0){
            r = (*func)();
        }
    }

    // Cleanup

    if (lib){
        CloseLibrary(lib);
    }

    return r;
}

