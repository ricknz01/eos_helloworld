#ifndef HELLOWORD
#define HELLOWORD
#include <eosio/eosio.hpp>
#include <pet.hpp>
#include <balance.hpp>

CONTRACT helloworld: public eosio::contract {
  public:
    using eosio::contract::contract;
    helloworld(eosio::name receiver, eosio::name code, eosio::datastream<const char *> ds) :contract(receiver, code, ds), currency_symbol("ICO", 4){}
    ACTION ap();
    ACTION hi(eosio::name const & nm);
    ACTION addpet(uint64_t const id, eosio::name const & owner, eosio::name const & pets_name, uint64_t const age, eosio::name const & type);
    ACTION modifypet(uint64_t const id, eosio::name const & owner, eosio::name const & pets_name, uint64_t const age, eosio::name const & type);
    ACTION removepet(uint64_t const id);
    ACTION showpet(uint64_t const id);
    ACTION petowedby(eosio::name const &owner);
    ACTION notify(eosio::name user, std::string msg);
    eosio::symbol currency_symbol;
    [[eosio::on_notify("eosio.token::transfer")]]
    void pay(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo);

};



#endif 