export ANDROID_NDK='/Users/furture/Library/Android/android-ndk-r15c'
if [ "${ANDROID_NDK}" == "" ]; then
    echo "Please Config ANDROID_NDK path"
    exit 5
fi
export CMAKE_SYSROOT=${ANDROID_NDK}/platforms/android-16/arch-arm/
export CMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake
export ANDROID_API=14
export CMAKE_SYSTEM_VERSION=14
export ANDROID_PLATFORM=android-14
export ANDROID_STL=gnustl_static
rm -rf ./out
mkdir ./out
cd out
cmake -DCMAKE_SYSTEM_NAME=Android -DANDROID_ABI=armeabi-v7a -DCMAKE_BUILD_TYPE=Release -DANDROID_NDK=${ANDROID_NDK} -DANDROID_STL=${ANDROID_STL} -DANDROID_PLATFORM=android-14 -DANDROID_TOOLCHAIN=gcc -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake --build ../
