export ANDROID_NDK=/Users/furture/Library/Android/android-ndk-r15c
rm -rf out/symbol
mkdir  out/symbol
cp out/libweexrender.so out/symbol/libweexrender.so
${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/arm-linux-androideabi/bin/strip -s out/libweexrender.so

##${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/arm-linux-androideabi/bin/strip -s out/third_party/*.a
##${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/arm-linux-androideabi/bin/strip -s out/render/*.a
##${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/arm-linux-androideabi/bin/strip -s out/render/core/*.a

##${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/arm-linux-androideabi/bin/strip -s libweexrender.so
