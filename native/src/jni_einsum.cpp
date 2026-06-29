#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Einstein summation
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeEinsum(JNIEnv* env, jclass, jstring subscripts, jobjectArray operands) {
    try {
        std::string subscriptsStr = jstringToString(env, subscripts);
        auto ptrVec = toArrayVec(env, operands);
        std::vector<npc::Array> operandsVec;
        operandsVec.reserve(ptrVec.size());
        for (auto* ptr : ptrVec) {
            if (!ptr) {
                throwNpcException(env, "einsum: null operand in array");
                return 0;
            }
            operandsVec.push_back(*ptr);
        }
        return wrapArray(std::make_unique<npc::Array>(npc::einsum(subscriptsStr.c_str(), operandsVec)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "einsum: unknown error");
        return 0;
    }
}

} // extern "C"
