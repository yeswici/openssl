/*
 * Copyright 2017-2018 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <oqs/oqs.h>

/*
 * Certificate table information. NB: table entries must match SSL_PKEY indices
 */
static const SSL_CERT_LOOKUP ssl_cert_info [] = {
    {EVP_PKEY_RSA, SSL_aRSA}, /* SSL_PKEY_RSA */
    {EVP_PKEY_RSA_PSS, SSL_aRSA}, /* SSL_PKEY_RSA_PSS_SIGN */
    {EVP_PKEY_DSA, SSL_aDSS}, /* SSL_PKEY_DSA_SIGN */
    {EVP_PKEY_EC, SSL_aECDSA}, /* SSL_PKEY_ECC */
    {NID_id_GostR3410_2001, SSL_aGOST01}, /* SSL_PKEY_GOST01 */
    {NID_id_GostR3410_2012_256, SSL_aGOST12}, /* SSL_PKEY_GOST12_256 */
    {NID_id_GostR3410_2012_512, SSL_aGOST12}, /* SSL_PKEY_GOST12_512 */
    {EVP_PKEY_ED25519, SSL_aECDSA}, /* SSL_PKEY_ED25519 */
    {EVP_PKEY_ED448, SSL_aECDSA}, /* SSL_PKEY_ED448 */
///// OQS_TEMPLATE_FRAGMENT_GIVE_SSL_CERT_INFO_START
    {EVP_PKEY_OQS_SIG_DEFAULT, SSL_aOQS_SIG_DEFAULT}, /* SSL_PKEY_OQS_SIG_DEFAULT */
    {EVP_PKEY_P256_OQS_SIG_DEFAULT, SSL_aP256_OQS_SIG_DEFAULT}, /* SSL_PKEY_P256_OQS_SIG_DEFAULT */
    {EVP_PKEY_RSA3072_OQS_SIG_DEFAULT, SSL_aRSA3072_OQS_SIG_DEFAULT}, /* SSL_PKEY_RSA3072_OQS_SIG_DEFAULT */
    {EVP_PKEY_DILITHIUM2, SSL_aDILITHIUM2}, /* SSL_PKEY_DILITHIUM2 */
    {EVP_PKEY_P256_DILITHIUM2, SSL_aP256_DILITHIUM2}, /* SSL_PKEY_P256_DILITHIUM2 */
    {EVP_PKEY_RSA3072_DILITHIUM2, SSL_aRSA3072_DILITHIUM2}, /* SSL_PKEY_RSA3072_DILITHIUM2 */
    {EVP_PKEY_DILITHIUM3, SSL_aDILITHIUM3}, /* SSL_PKEY_DILITHIUM3 */
    {EVP_PKEY_P256_DILITHIUM3, SSL_aP256_DILITHIUM3}, /* SSL_PKEY_P256_DILITHIUM3 */
    {EVP_PKEY_RSA3072_DILITHIUM3, SSL_aRSA3072_DILITHIUM3}, /* SSL_PKEY_RSA3072_DILITHIUM3 */
    {EVP_PKEY_DILITHIUM4, SSL_aDILITHIUM4}, /* SSL_PKEY_DILITHIUM4 */
    {EVP_PKEY_P384_DILITHIUM4, SSL_aP384_DILITHIUM4}, /* SSL_PKEY_P384_DILITHIUM4 */
    {EVP_PKEY_FALCON512, SSL_aFALCON512}, /* SSL_PKEY_FALCON512 */
    {EVP_PKEY_P256_FALCON512, SSL_aP256_FALCON512}, /* SSL_PKEY_P256_FALCON512 */
    {EVP_PKEY_RSA3072_FALCON512, SSL_aRSA3072_FALCON512}, /* SSL_PKEY_RSA3072_FALCON512 */
    {EVP_PKEY_FALCON1024, SSL_aFALCON1024}, /* SSL_PKEY_FALCON1024 */
    {EVP_PKEY_P521_FALCON1024, SSL_aP521_FALCON1024}, /* SSL_PKEY_P521_FALCON1024 */
    {EVP_PKEY_MQDSS3148, SSL_aMQDSS3148}, /* SSL_PKEY_MQDSS3148 */
    {EVP_PKEY_P256_MQDSS3148, SSL_aP256_MQDSS3148}, /* SSL_PKEY_P256_MQDSS3148 */
    {EVP_PKEY_RSA3072_MQDSS3148, SSL_aRSA3072_MQDSS3148}, /* SSL_PKEY_RSA3072_MQDSS3148 */
    {EVP_PKEY_PICNICL1FS, SSL_aPICNICL1FS}, /* SSL_PKEY_PICNICL1FS */
    {EVP_PKEY_P256_PICNICL1FS, SSL_aP256_PICNICL1FS}, /* SSL_PKEY_P256_PICNICL1FS */
    {EVP_PKEY_RSA3072_PICNICL1FS, SSL_aRSA3072_PICNICL1FS}, /* SSL_PKEY_RSA3072_PICNICL1FS */
    {EVP_PKEY_PICNIC2L1FS, SSL_aPICNIC2L1FS}, /* SSL_PKEY_PICNIC2L1FS */
    {EVP_PKEY_P256_PICNIC2L1FS, SSL_aP256_PICNIC2L1FS}, /* SSL_PKEY_P256_PICNIC2L1FS */
    {EVP_PKEY_RSA3072_PICNIC2L1FS, SSL_aRSA3072_PICNIC2L1FS}, /* SSL_PKEY_RSA3072_PICNIC2L1FS */
    {EVP_PKEY_QTESLAPI, SSL_aQTESLAPI}, /* SSL_PKEY_QTESLAPI */
    {EVP_PKEY_P256_QTESLAPI, SSL_aP256_QTESLAPI}, /* SSL_PKEY_P256_QTESLAPI */
    {EVP_PKEY_RSA3072_QTESLAPI, SSL_aRSA3072_QTESLAPI}, /* SSL_PKEY_RSA3072_QTESLAPI */
    {EVP_PKEY_QTESLAPIII, SSL_aQTESLAPIII}, /* SSL_PKEY_QTESLAPIII */
    {EVP_PKEY_P384_QTESLAPIII, SSL_aP384_QTESLAPIII}, /* SSL_PKEY_P384_QTESLAPIII */
    {EVP_PKEY_RAINBOWIACLASSIC, SSL_aRAINBOWIACLASSIC}, /* SSL_PKEY_RAINBOWIACLASSIC */
    {EVP_PKEY_P256_RAINBOWIACLASSIC, SSL_aP256_RAINBOWIACLASSIC}, /* SSL_PKEY_P256_RAINBOWIACLASSIC */
    {EVP_PKEY_RSA3072_RAINBOWIACLASSIC, SSL_aRSA3072_RAINBOWIACLASSIC}, /* SSL_PKEY_RSA3072_RAINBOWIACLASSIC */
    {EVP_PKEY_RAINBOWVCCLASSIC, SSL_aRAINBOWVCCLASSIC}, /* SSL_PKEY_RAINBOWVCCLASSIC */
    {EVP_PKEY_P521_RAINBOWVCCLASSIC, SSL_aP521_RAINBOWVCCLASSIC}, /* SSL_PKEY_P521_RAINBOWVCCLASSIC */
    {EVP_PKEY_SPHINCSHARAKA128FROBUST, SSL_aSPHINCSHARAKA128FROBUST}, /* SSL_PKEY_SPHINCSHARAKA128FROBUST */
    {EVP_PKEY_P256_SPHINCSHARAKA128FROBUST, SSL_aP256_SPHINCSHARAKA128FROBUST}, /* SSL_PKEY_P256_SPHINCSHARAKA128FROBUST */
    {EVP_PKEY_RSA3072_SPHINCSHARAKA128FROBUST, SSL_aRSA3072_SPHINCSHARAKA128FROBUST}, /* SSL_PKEY_RSA3072_SPHINCSHARAKA128FROBUST */
///// OQS_TEMPLATE_FRAGMENT_GIVE_SSL_CERT_INFO_END
};
