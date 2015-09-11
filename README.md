# README #

Welcome to the Opus demo for Linux server.

### Summary ###

The is a demo on how to use Opus codec for Linux server. It can encode an opus file to memory buffer and decode the buffer to an opus file.  


### Getting started ###

* pre-requisites  

1. JDK v1.8 or higher  
2. Eclipse

* Summary of set up:

1. Get the source code.[Git] (https://bitbucket.org/louisyoung/opus_linux.git)  
2. Open it in Eclipse. 
3. Compile and run.  

### Usage ###

```
OpusTool tool = new OpusTool();
String fin = "xxx", fout = "xxx";
ByteBuffer buf = tool.decode(fin, null);
tool.encode(buf, fout, null);    
tool.releaseByteBuffer(buf);//free memory
```

### Hints ###

1. top.oply.opuslib.OpusTool contains the basic codec functions.
2. If Ubuntu 64 bit server, the native library libopusTool.so under the folder "libs" can be used directly.
3. Compiling Native code is easy, just go to "\src\jni", and issue command "make". Then copy  libopusTool.so to "libs".  

### Open Projects ###

1. Opus (git://git.opus-codec.org/opus.git)

2. Opus-tools (git://git.xiph.org/opus-tools.git)

3. Opusfile (git://git.xiph.org/opusfile.git)

### Enjoy ###