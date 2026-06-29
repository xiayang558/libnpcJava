#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// 1-D Histogram
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jobject JNICALL
Java_libnpc_Npc_nativeHistogram(JNIEnv* env, jclass, jlong xHandle, jint bins, jboolean density) {
    try {
        auto* x = unwrapArray(xHandle);
        checkNotNull(env, xHandle, "histogram");
        auto result = npc::histogram(*x, static_cast<int>(bins), density == JNI_TRUE);

        jclass cls = env->FindClass("libnpc/HistogramResult");
        jmethodID ctor = env->GetMethodID(cls, "<init>",
            "(Llibnpc/NpcArray;Llibnpc/NpcArray;)V");

        jobject histObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.hist))));
        jobject binEdgesObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.bin_edges))));

        return env->NewObject(cls, ctor, histObj, binEdgesObj);
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

// ═══════════════════════════════════════════════════════════════════
// 2-D Histogram
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jobject JNICALL
Java_libnpc_Npc_nativeHistogram2d(JNIEnv* env, jclass,
                                   jlong xHandle, jlong yHandle,
                                   jint binsX, jint binsY,
                                   jlong rangeXHandle, jlong rangeYHandle,
                                   jboolean density) {
    try {
        auto* x = unwrapArray(xHandle);
        auto* y = unwrapArray(yHandle);
        checkNotNull(env, xHandle, "histogram2d");
        checkNotNull(env, yHandle, "histogram2d");

        npc::Array range_x = rangeXHandle != 0 ? npc::Array(*unwrapArray(rangeXHandle)) : npc::Array();
        npc::Array range_y = rangeYHandle != 0 ? npc::Array(*unwrapArray(rangeYHandle)) : npc::Array();

        auto result = npc::histogram2d(*x, *y,
                                       static_cast<int>(binsX), static_cast<int>(binsY),
                                       range_x, range_y,
                                       density == JNI_TRUE);

        jclass cls = env->FindClass("libnpc/Histogram2DResult");
        jmethodID ctor = env->GetMethodID(cls, "<init>",
            "(Llibnpc/NpcArray;Llibnpc/NpcArray;Llibnpc/NpcArray;)V");

        jobject hObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.H))));
        jobject xEdgesObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.x_edges))));
        jobject yEdgesObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.y_edges))));

        return env->NewObject(cls, ctor, hObj, xEdgesObj, yEdgesObj);
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

// ═══════════════════════════════════════════════════════════════════
// N-D Histogram
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jobject JNICALL
Java_libnpc_Npc_nativeHistogramdd(JNIEnv* env, jclass,
                                   jlong sampleHandle, jlong binsHandle,
                                   jlong rangeHandle, jboolean density) {
    try {
        auto* sample = unwrapArray(sampleHandle);
        auto* bins = unwrapArray(binsHandle);
        checkNotNull(env, sampleHandle, "histogramdd");
        checkNotNull(env, binsHandle, "histogramdd");

        npc::Array range = rangeHandle != 0 ? npc::Array(*unwrapArray(rangeHandle)) : npc::Array();

        auto result = npc::histogramdd(*sample, *bins, range, density == JNI_TRUE);

        jclass cls = env->FindClass("libnpc/HistogramDDResult");
        jmethodID ctor = env->GetMethodID(cls, "<init>",
            "(Llibnpc/NpcArray;[Llibnpc/NpcArray;)V");

        jobject histObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.hist))));

        // Convert vector<Array> edges to NpcArray[]
        jclass npcArrayCls = env->FindClass("libnpc/NpcArray");
        jobjectArray edgesArr = env->NewObjectArray(
            static_cast<jsize>(result.edges.size()), npcArrayCls, nullptr);
        for (size_t i = 0; i < result.edges.size(); ++i) {
            jlong h = wrapArray(std::make_unique<npc::Array>(std::move(result.edges[i])));
            jobject obj = createNpcArrayObject(env, h);
            env->SetObjectArrayElement(edgesArr, static_cast<jsize>(i), obj);
            env->DeleteLocalRef(obj);
        }

        return env->NewObject(cls, ctor, histObj, edgesArr);
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

} // extern "C"
