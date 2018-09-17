/*
 * Copyright 2018 Vizor Games LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
#include "InfraworldRuntime.h"
#include "ChannelCredentials.h"

#include <grpc++/security/credentials.h>

// Since GRPC actively uses winapi, we need to forbid windows macros
// (such as GetMessage, MemoryBarrier, etc.) in our remaining code.
// To do it, we 'wrap' all the C++ file's including ANY GRPC header files
// content into Allow/Hide WindowsPlatformTypes.
// We're unable to 'isolate' the WinAPI usage within a single C++ file thanks to Unity Build.
#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#endif

UChannelCredentials* UChannelCredentials::MakeGoogleDefaultCredentials()
{
    return NewObject<UGoogleDefaultCredentials>();
}

UChannelCredentials* UChannelCredentials::MakeSslCredentials(FString PemRootCerts, FString PemPrivateKey, FString PemCertChain)
{
    USslCredentials* const SslCredentials = NewObject<USslCredentials>();

    SslCredentials->PemRootCerts = PemRootCerts;
    SslCredentials->PemPrivateKey = PemPrivateKey;
    SslCredentials->PemCertChain = PemCertChain;

    return SslCredentials;
}

UChannelCredentials* UChannelCredentials::MakeInsecureChannelCredentials()
{
    return NewObject<UInsecureChannelCredentials>();
}

#if PLATFORM_WINDOWS
#include "HideWindowsPlatformTypes.h"
#endif
