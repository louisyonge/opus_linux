#include "config.h"
#ifdef JAVA_V

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "top_oply_opuslib_OpusTool.h"
#include "opusaudio.h"
#include "log.h"
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    jstrToChar
     * Signature:
     * conver jstring to char*, return the lenth of that string
     */

    int jstrToChar(JNIEnv *env,jstring inStr, char *outBuffer) {
      if (inStr == NULL)
        return 0;
      int len = 0;
      len = (*env)->GetStringLength(env, inStr);
      (*env)->GetStringUTFRegion(env, inStr, 0, len, outBuffer);
      return len;
    }


    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    nativeGetString
     * Signature: ()Ljava/lang/String;
     */
    JNIEXPORT jstring JNICALL Java_top_oply_opuslib_OpusTool_nativeGetString
      (JNIEnv *env, jobject obj) {

      char buf[] = "Hello from OpusTool!";
      return (*env)->NewStringUTF(env, buf);
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    encode
     * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_encode__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2
      (JNIEnv *env, jobject obj, jstring fileIn, jstring fileOut, jstring option) {

      char bufFileIn[256] = {0}, bufFileOut[256] = {0}, bufFileOp[MAX_CMD_BUFFER] = {0};
      int rst = 1;
      jstrToChar(env, fileIn, bufFileIn);
      jstrToChar(env, fileOut, bufFileOut);
      jstrToChar(env, option, bufFileOp);
      rst = encode_c(bufFileIn, bufFileOut, bufFileOp, NULL);
      return rst;
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    decode
     * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_decode__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2
      (JNIEnv *env, jobject obj, jstring fileIn, jstring fileOut, jstring option) {

        char bufFileIn[256] = {0}, bufFileOut[256] = {0}, bufFileOp[MAX_CMD_BUFFER] = {0};
        int rst = 1;
        jstrToChar(env, fileIn, bufFileIn);
        jstrToChar(env, fileOut, bufFileOut);
        jstrToChar(env, option, bufFileOp);
        rst = decode_c(bufFileIn, bufFileOut, bufFileOp, NULL);
        return rst;
      }


    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    encode
     * Signature: (Ljava/nio/ByteBuffer;Ljava/lang/String;Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_encode__Ljava_nio_ByteBuffer_2Ljava_lang_String_2Ljava_lang_String_2
      (JNIEnv *env, jobject obj, jobject buffer, jstring fileOut, jstring option) {
        char bufFileOut[256] = {0}, bufFileOp[MAX_CMD_BUFFER] = {0};
        int rst = 1;
        char bufFileIn[] = "ThisStringisNeeded.wav";
        jstrToChar(env, fileOut, bufFileOut);
        jstrToChar(env, option, bufFileOp);

        unsigned char *addr = (*env)->GetDirectBufferAddress(env, buffer);
        long capacity = (*env)->GetDirectBufferCapacity(env, buffer);

        if(!addr || capacity == 0) {
            perror("bytebuffer correpted!");
            return -1;
        }
	LOGD("enc fmem\n");
        FILE *fmem = fmemopen(addr, capacity, "rb");
        if(!fmem) {
            perror("open memory file failed!");
            return -1;
        }
	
        rst = encode_c(bufFileIn, bufFileOut, bufFileOp, fmem);
        return rst;
      }


    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    decode
     * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/nio/ByteBuffer;
     */
    JNIEXPORT jobject JNICALL Java_top_oply_opuslib_OpusTool_decode__Ljava_lang_String_2Ljava_lang_String_2
      (JNIEnv *env, jobject obj, jstring fileIn, jstring option) {
        char bufFileIn[256] = {0}, bufFileOp[MAX_CMD_BUFFER] = {0};

        char bufFileOut[] = "ThisStringisNeeded.wav";
        jstrToChar(env, fileIn, bufFileIn);
        jstrToChar(env, option, bufFileOp);
        int rst = 1;
        unsigned char * addr = NULL;
        long capacity = 0;
        FILE *fmem = open_memstream(&addr, &capacity);
        if(!fmem) {
            perror("open memory file failed!");
            return NULL;
        }
	
        rst = decode_c(bufFileIn, bufFileOut, bufFileOp, fmem);

        if(rst == 0) {
            jobject buf = (*env)->NewDirectByteBuffer(env, addr, capacity);
            return buf;
        }
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    releaseByteBuffer
     * Signature: (Ljava/nio/ByteBuffer;)V
     */
    JNIEXPORT void JNICALL Java_top_oply_opuslib_OpusTool_releaseByteBuffer
      (JNIEnv *env, jobject obj, jobject buffer) {
        void *addr = (*env)->GetDirectBufferAddress(env, buffer);
        if(addr)
            free(addr);
      }


    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    startRecording
     * Signature: (Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_startRecording
      (JNIEnv *env, jobject obj, jstring fileIn){
      char bufFileIn[256] = {0};
      jstrToChar(env, fileIn, bufFileIn);
      return startRecording(bufFileIn);
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    stopRecording
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_top_oply_opuslib_OpusTool_stopRecording
      (JNIEnv *env, jobject obj) {
        return stopRecording();
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    play
     * Signature: (Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_play
      (JNIEnv *env, jobject obj, jstring fileIn){

       char bufFileIn[256] = {0};
       jstrToChar(env, fileIn, bufFileIn);

    //return play(bufFileIn);
    //to do:  no need to
      return 0;
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    stopPlaying
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_top_oply_opuslib_OpusTool_stopPlaying
      (JNIEnv *env, jobject obj) {
    //	stopPlaying();
    //to do:
      return;
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    writeFrame
     * Signature: (Ljava/nio/ByteBuffer;I)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_writeFrame
      (JNIEnv *env, jobject obj, jobject buffer, jint len) {

      jbyte *bufferBytes = (*env)->GetDirectBufferAddress(env, buffer);
      return writeFrame(bufferBytes, len);
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    isOpusFile
     * Signature: (Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_isOpusFile
      (JNIEnv *env, jobject obj, jstring fileIn){
       char bufFileIn[256] = {0};
       jstrToChar(env, fileIn, bufFileIn);

      return isOpusFile(bufFileIn);
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    openOpusFile
     * Signature: (Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_openOpusFile
      (JNIEnv *env, jobject obj, jstring fileIn){
      char bufFileIn[256] = {0};
      jstrToChar(env, fileIn, bufFileIn);

      return openOpusFile(bufFileIn);
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    seekOpusFile
     * Signature: (F)I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_seekOpusFile
      (JNIEnv *env, jobject obj, jfloat position) {
      return seekOpusFile(position);
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    closeOpusFile
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_top_oply_opuslib_OpusTool_closeOpusFile
      (JNIEnv *env, jobject obj) {
      return closeOpusFile();
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    readOpusFile
     * Signature: (Ljava/nio/ByteBuffer;I)V
     */
    JNIEXPORT void JNICALL Java_top_oply_opuslib_OpusTool_readOpusFile
      (JNIEnv *env, jobject obj, jobject buffer, jint capacity) {

      jbyte *bufferBytes = (*env)->GetDirectBufferAddress(env, buffer);
      return readOpusFile(bufferBytes, capacity);
      }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    getFinished
     * Signature: ()I
     */
    JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_getFinished
      (JNIEnv *env, jobject obj) {
      return getFinished();
      }


/*
    * Class:     top_oply_opuslib_OpusTool
    * Method:    getSize
    * Signature: ()I
    */
   JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_getSize
     (JNIEnv *env, jobject obj) {
     return getSize();
     }

   /*
   * Class:     top_oply_opuslib_OpusTool
   * Method:    getChannelCount
   * Signature: ()I
   */
  JNIEXPORT jint JNICALL Java_top_oply_opuslib_OpusTool_getChannelCount
    (JNIEnv *env, jobject obj) {
    return getChannelCount();
    }

    /*
    * Class:     top_oply_opuslib_OpusTool
    * Method:    getPcmOffset
    * Signature: ()J
    */
    JNIEXPORT jlong JNICALL Java_top_oply_opuslib_OpusTool_getPcmOffset
    (JNIEnv *env, jobject obj) {
    return getPcmOffset();
    }

    /*
     * Class:     top_oply_opuslib_OpusTool
     * Method:    getTotalPcmDuration
     * Signature: ()J
     */
    JNIEXPORT jlong JNICALL Java_top_oply_opuslib_OpusTool_getTotalPcmDuration
      (JNIEnv *env, jobject obj) {
      return getTotalPcmDuration();
      }

#ifdef __cplusplus
}
#endif

#endif
