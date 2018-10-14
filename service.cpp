/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "android.hardware.biometrics.fingerprint@2.1-service"

#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>
#include "BiometricsFingerprint.h"
#include "BiometricsFingerprint_efp.h"

using android::NO_ERROR;
using android::sp;
using android::status_t;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::hardware::biometrics::fingerprint::V2_1::IBiometricsFingerprint;
using android::hardware::biometrics::fingerprint::V2_1::implementation::BiometricsFingerprint;
using android::hardware::biometrics::fingerprint::V2_1::implementation::BiometricsFingerprint_efp;

int main() {
#ifdef USE_FPC_NILE
    android::sp<IBiometricsFingerprint> bio = new BiometricsFingerprint_efp();
#else
    android::sp<IBiometricsFingerprint> bio = BiometricsFingerprint::getInstance();
#endif

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (bio != nullptr) {
        status_t status = bio->registerAsService();
        if (status != NO_ERROR) {
            ALOGE("Cannot start fingerprint service: %d", status);
            return 1;
        }
    } else {
        ALOGE("Can't create instance of BiometricsFingerprint, nullptr");
        return 1;
    }

    joinRpcThreadpool();

    return 0;  // should never get here
}
