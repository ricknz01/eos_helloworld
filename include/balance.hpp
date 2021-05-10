#ifndef BALANCE
#define BALANCE
#include <eosio/asset.hpp>

struct [[eosio::table, eosio::contract("helloworld")]] balance_t {
    public:
        eosio::asset funds;
        uint64_t primary_key() const {return funds.symbol.raw();}


};

typedef eosio::multi_index< "balances"_n, balance_t> balance_index;
#endif