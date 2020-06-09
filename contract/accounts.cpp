#include <eosio/eosio.hpp>
#include <eosio.token/eosio.token.hpp>

using namespace eosio;

class Accounts : eosio::contract {
    struct [[eosio::table]] account_balance
    {
	name user;
        std::map<name, asset> type_balance;
        uint64_t primary_key() const { return user.value; }
    };

    using accounts_table = eosio::multi_index<"user.name.ind"_n, account_balance>;

  public:
    // Use contract's constructor
    using contract::contract;

    // Post a message
    [[eosio::action]] void deposit(name user, name acc_type, asset amount) {


        // Check user
        require_auth(user);

	check(amount.to_real() > 0.0, "Invalid amount to deposit, "+amount.to_string());

        accounts_table accounts{get_self(), 0};

	auto& account = accounts.get(user.value);//throws exception if account doesnt exists for user
	account.type_balance[acc_type]  += asset;
	
	//update
	accounts.modify(account);
    }
};
