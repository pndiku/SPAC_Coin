// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x40;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0xa7;
        pchMessageStart[3] = 0xd4;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 38037;
        nRPCPort = 38038;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //genesis.nTime = 1508256000
        //genesis.nNonce = 99278
        //genesis.nVersion = 1
        //genesis.GetHash = 00000b10bb0b10999b6bdae068317b90e8770ff8c28dd206e3d131c9b65d257e
        //genesis.hashMerkleRoot = 287ad74b0ffdf4a2aee1438d3a17b71cb7ca0bdaeede3fee8d44e9ae5aff1959


        const char* pszTimestamp = "2017, November 14, Single Productive African Coin";
        CTransaction txNew;
        txNew.nTime = 1508256000;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1508256000;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 99278;
// uncomment to log genesis block info
//      //  start
/*        if (true && genesis.GetHash() != hashGenesisBlock)
                       {
                          printf("Searching for genesis block...\n");
                           uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                           uint256 thash;

                           while (true)
                           {
                               thash = genesis.GetHash();
                               if (thash <= hashTarget)
                                   break;
                               if ((genesis.nNonce & 0xFFF) == 0)
                               {
                                   printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                               }
                               ++genesis.nNonce;
                               if (genesis.nNonce == 0)
                               {
                                   printf("NONCE WRAPPED, incrementing time\n");
                                   ++genesis.nTime;
                               }
                           }
                           printf("genesis.nTime = %u \n", genesis.nTime);
                           printf("genesis.nNonce = %u \n", genesis.nNonce);
                           printf("genesis.nVersion = %u \n", genesis.nVersion);
                           printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
                           printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root

                       }

//        //end*/
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000b10bb0b10999b6bdae068317b90e8770ff8c28dd206e3d131c9b65d257e"));
        assert(genesis.hashMerkleRoot == uint256("0x287ad74b0ffdf4a2aee1438d3a17b71cb7ca0bdaeede3fee8d44e9ae5aff1959"));

        vSeeds.push_back(CDNSSeedData("nodea.SpacCoin.com", "nodea.SpacCoin.com"));
        vSeeds.push_back(CDNSSeedData("nodeb.SpacCoin.com", "nodeb.SpacCoin.com"));
        vSeeds.push_back(CDNSSeedData("nodec.SpacCoin.com", "nodec.SpacCoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(63);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(55);
        base58Prefixes[SECRET_KEY] =     list_of(191);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x68)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x58)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        //genesis.nTime = 1508256000
        //genesis.nNonce = 63704
        //genesis.nVersion = 1
        //genesis.hashMerkleRoot = 287ad74b0ffdf4a2aee1438d3a17b71cb7ca0bdaeede3fee8d44e9ae5aff1959
        //genesis.GetHash = 0000f5b356612ddc560aa7ba3fe28f09c724a34083667cf206d5686c06390710



        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xf7;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0x0c;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("");
        nDefaultPort = 48647;
        nRPCPort = 48648;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 63704;
//uncomment to log genesis block info
//
/*          if (true && genesis.GetHash() != hashGenesisBlock)
                         {
                             printf("Searching for genesis block...\n");
                             uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                             uint256 thash;

                             while (true)
                             {
                                 thash = genesis.GetHash();
                                 if (thash <= hashTarget)
                                     break;
                                 if ((genesis.nNonce & 0xFFF) == 0)
                                 {
                                     printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                                 }
                                 ++genesis.nNonce;
                                 if (genesis.nNonce == 0)
                                 {
                                     printf("NONCE WRAPPED, incrementing time\n");
                                     ++genesis.nTime;
                                }
                             }
                             printf("genesis.nTime = %u \n", genesis.nTime);
                             printf("genesis.nNonce = %u \n", genesis.nNonce);
                             printf("genesis.nVersion = %u \n", genesis.nVersion);
                             printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //idk
                             printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());

                         }

//*/
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000f5b356612ddc560aa7ba3fe28f09c724a34083667cf206d5686c06390710"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//genesis.nTime = 1508256000
//genesis.nNonce = 0
//genesis.nVersion = 1
//genesis.hashMerkleRoot = 287ad74b0ffdf4a2aee1438d3a17b71cb7ca0bdaeede3fee8d44e9ae5aff1959
//genesis.GetHash = 262200031538e2f55244ad54372b89596a75ff079847f38ace8508f2266dbeef



class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xac;
        pchMessageStart[2] = 0xbd;
        pchMessageStart[3] = 0xcd;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1508256000;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 38444;
        strDataDir = "regtest";
//uncomment to log regtest genesis block info
//
/*        if (true)
                         {
                             printf("Searching for genesis block...\n");
                             uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                             uint256 thash;

                             while (true)
                             {
                                 thash = genesis.GetHash();
                                 if (thash <= hashTarget)
                                     break;
                                 if ((genesis.nNonce & 0xFFF) == 0)
                                 {
                                     printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                                 }
                                 ++genesis.nNonce;
                                 if (genesis.nNonce == 0)
                                 {
                                     printf("NONCE WRAPPED, incrementing time\n");
                                     ++genesis.nTime;
                                 }
                             }
                             printf("genesis.nTime = %u \n", genesis.nTime);
                             printf("genesis.nNonce = %u \n", genesis.nNonce);
                             printf("genesis.nVersion = %u \n", genesis.nVersion);
                             printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //idk
                             printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());

                         }

//*/
        assert(hashGenesisBlock == uint256("0x262200031538e2f55244ad54372b89596a75ff079847f38ace8508f2266dbeef"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
