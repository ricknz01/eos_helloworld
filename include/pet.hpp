#ifndef PET
#define PET
class [[eosio::table, eosio::contract("helloworld")]] pet_t {
    private:
        uint64_t id;
        eosio::name owner;
        eosio::name pet_name;
        uint64_t age;
        eosio::name type;
    public:
        pet_t(){};
        pet_t(uint64_t const _id,
            eosio::name const & _owner,
            eosio::name const & _pet_name,
            uint64_t const _age,
            eosio::name const & _type):
                id(_id), owner(_owner), pet_name(_pet_name), age(_age), type(_type){}
        uint64_t get_id() const {return id;}
        eosio::name get_owner() const {return owner;}
        uint64_t get_owner_valeu() const{return owner.value;}
        eosio::name get_pet_name() const {return pet_name;}
        uint64_t get_age() const {return age;}
        eosio::name get_type() const {return type;}
        uint64_t primary_key() const {return get_id();}
    EOSLIB_SERIALIZE(pet_t, (id)(owner)(pet_name)(age)(type))
};

typedef eosio::multi_index< "pets"_n, pet_t, eosio::indexed_by<"byowner"_n, eosio::const_mem_fun<pet_t, uint64_t, &pet_t::get_owner_valeu>>> pets_table;
#endif