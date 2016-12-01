#!/bin/bash

# ============================================================================
# Name        : build_ios.sh
# Author      : Przemyslaw Zygmunt p.zygmunt@acsoftware.pl [AC SOFTWARE]
# Version     : 1.0
# Copyright   : GPLv2
# ============================================================================


SDK_VERSION="9.3"
BUILD_CFG="Release"
IOS_OPENSSL_LIB_INC="../../OpenSSL-for-iPhone/include"

OS=`uname -s`

case $OS in
Darwin)
    ;;
*)
    echo
    echo "Supported only on macOS!"
    echo
    exit 1
    ;;
esac

BUILD_DIR="./"$BUILD_CFG
DEVELOPER=`xcode-select -print-path`

if [ ! -d $BUILD_DIR ]; then
    echo "Build dir does not exists! " $BUILD_DIR;
    exit;
fi


if [ ! -d "${DEVELOPER}/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS${SDK_VERSION}.sdk" ]; then
    if [ ! -f Xcode_7.3.1.dmg ]; then
        echo
        echo "Please download Xcode and place here."
        echo "Download link: http://adcdownload.apple.com/Developer_Tools/Xcode_7.3.1/Xcode_7.3.1.dmg"
        echo "Then re-run this script again."
        echo
        exit 1
    fi
    echo "Mounting Xcode installer..."
    hdiutil attach Xcode_7.3.1.dmg -noverify -nobrowse -mountpoint /Volumes/xcode
    echo "Copying iPhoneOS${SDK_VERSION}.sdk..."
    sudo cp -RL /Volumes/xcode/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS${SDK_VERSION}.sdk \
        ${DEVELOPER}/Platforms/iPhoneOS.platform/Developer/SDKs/
    if [ ! -d "${DEVELOPER}/Platforms/iPhoneSimulator.platform/Developer/iPhoneSimulator${SDK_VERSION}.sdk" ]; then
        echo "Copying iPhoneSimulator${SDK_VERSION}.sdk..."
        sudo cp -RL /Volumes/xcode/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator${SDK_VERSION}.sdk \
            ${DEVELOPER}/Platforms/iPhoneSimulator.platform/Developer/SDKs/
    fi
    echo "Unmounting Xcode installer..."
    hdiutil detach /Volumes/xcode
fi

build()
{
        ARCH=$1

        if [[ "${ARCH}" == "i386" || "${ARCH}" == "x86_64" ]]; then
                PLATFORM="iPhoneSimulator"
        else
                PLATFORM="iPhoneOS"
        fi

        cd $BUILD_DIR

        export CROSS_TOP="${DEVELOPER}/Platforms/${PLATFORM}.platform/Developer"
        export CROSS_SDK="${PLATFORM}${SDK_VERSION}.sdk"

        export PARAMS="-fembed-bitcode -I${IOS_OPENSSL_LIB_INC} -arch ${ARCH} -isysroot ${CROSS_TOP}/SDKs/${CROSS_SDK} -miphoneos-version-min=${SDK_VERSION}"

        make clean
        make

        mkdir -p ${ARCH}
        mv libsupla-client.a ${ARCH}
}

CWD=`pwd`

if [ ! -f "../OpenSSL-for-iPhone/lib/libssl.a" ]; then
    cd ../OpenSSL-for-iPhone
    ./build-libssl.sh --ios-sdk=${SDK_VERSION} --archs="x86_64 i386 arm64 armv7"
    cd $CWD
fi

build "armv7"
build "arm64"
build "x86_64"
build "i386"

echo $CWD
cd $CWD

lipo \
	"${BUILD_DIR}/armv7/libsupla-client.a" \
	"${BUILD_DIR}/arm64/libsupla-client.a" \
	"${BUILD_DIR}/x86_64/libsupla-client.a" \
	"${BUILD_DIR}/i386/libsupla-client.a" \
	-create -output "${BUILD_DIR}/libsupla-client.a"

