#include <helloworld.hpp>

using namespace eosio;

void helloworld::ap(){
  eosio::print("aps:");

}

void helloworld::hi(eosio::name const & nm){
  eosio::print("me: ", nm);
}

void helloworld::addpet(uint64_t const id, eosio::name const & owner, eosio::name const & pets_name, uint64_t const age, eosio::name const & type)
{
  require_auth(owner);
  pets_table pets(get_self(), get_self().value);  
  auto pet = pets.find(id);
  eosio::check(pet == pets.end(), "The id already exist");
  pets.emplace(get_self(), [&](auto & entry){
    entry = pet_t(id, owner, pets_name, age, type);
  }); 
  //send_summary(owner, "Add dog");
}

void helloworld::modifypet(uint64_t const id, eosio::name const & owner, eosio::name const & pets_name, uint64_t const age, eosio::name const & type){
  
  pets_table pets(get_self(), get_self().value);  
  auto pet = pets.find(id);
  require_auth(pet->get_owner());
  eosio::check(pet != pets.end(), "The id does not exist");
  pets.modify(pet, get_self(), [&](auto & entry){
    entry = pet_t(id, owner, pets_name, age, type);
  }); 
}
void helloworld::removepet(uint64_t const id){
  pets_table pets(get_self(), get_self().value);  
  auto pet = pets.find(id);
  eosio::check(pet != pets.end(), "The id does not exist");
  require_auth(pet->get_owner());
  pets.erase(pet);
}

void helloworld::showpet(uint64_t const id){
  pets_table pets(get_self(), get_self().value);
  auto pet = pets.find(id);
  eosio::check(pet != pets.end(), "Id does not exist");
  eosio::print("Pet with id ", id, " is called ", pet->get_pet_name());
}

void helloworld::petowedby(eosio::name const &owner){
  pets_table pets(get_self(), get_self().value);
  auto pets_by_owner = pets.get_index<"byowner"_n>();
  auto pets_lower = pets_by_owner.lower_bound(owner.value);
  auto pets_upper = pets_by_owner.upper_bound(owner.value);
  for (auto i = pets_lower; i != pets_upper; i++){
  eosio::print(owner, " has a pet called ", i->get_pet_name(), ".");
  } 
}

void helloworld::notify(eosio::name user, std::string msg){
  require_auth(get_self());
  require_recipient(user);
}

void helloworld::pay(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo){
  check(false, "notification handler triggered successfully");
  
  if(from == get_self() || to != get_self()){
    return;
  }
  check(quantity.amount > 0, "Not enough coins");
  check(quantity.symbol == currency_symbol, "Not the correct coin");
  balance_index balances(get_self(), from.value);
  auto iterator = balances.find(currency_symbol.raw());
  if(iterator != balances.end()){
    balances.modify(iterator, get_self(), [&](auto &row){
      row.funds += quantity;
    });
  } else {
    balances.emplace(get_self(), [&](auto &row){
      row.funds = quantity;
    });
  }
}
/*
void helloworld::send_summary(eosio::name const & owner, std::string message){
    action(
      permission_level{get_self(), "active"_n},
      get_self(),
      "notify"_n,
      std::make_tuple(owner, message)
    ).send();
  }
*/

