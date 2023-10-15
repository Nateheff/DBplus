/*
  Simple SQL DBMS By Nathan Heffington
   
 
*/

#include <iostream>
#include <string> 
#include <sstream>
#include <fstream>
#include <cstring>
#include <set>

#include "Lexer/scanner.h"
#include "Lexer/list.h"
#include "Parser/Construct.cpp"
#include "Disk_Space/Disk_SM.h"
#include "Disk_Space/FSM.h"
#include "Buffer_Manager/Buffer_PM.h"
#include "Catalog/Syst_Attr.h"
#include "Catalog/Syst_Index.h"
#include "Catalog/Syst_Root.h"
#include "Catalog/Syst_Rel.h"
#include "Catalog/Syst_Catalog.h"
#include "B_Tree.h"


#define SIZE_NAME_COLUMN 10
#define NUM_MEASUREMENTS 1
#define SIZE_PAGE 


#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute);

enum Meta_Results {META_SUCCESS,META_FOREIGN};
enum Result {SUCCESS, FAILURE};



Meta_Results do_meta(std::string cmd){
    if(cmd == std::string{".exit"})
        exit(EXIT_SUCCESS);
    else{
        return META_FOREIGN;
    }
}



int main()
{
    /*
    Keyword_List res_list = {{{"bool",0},{"char",1},{"create",2},{"database",3},{"float",4},{"from",5},{"insert",6},{"int",7},{"key",8},{"primary",9},{"select",10},{"table",11},{"varchar",12},{"where",13},{"between",14},{"drop",15},{"delete",16},{"update",17}},18,9};
    std::unordered_map<std::string,uint16_t>operators{{"*",19},{">",20},{"<",21},{"/",22},{"(",23},{")",24},{"=",25},{"+",26},{"-",27},{"<=",28},{">=",29},{"<>",30}};
    std::string query;
    
    std::getline(std::cin,query);
    
    Scanner test(query,&res_list,operators);
    test.scanner_run();
    test.print_query();
    receiver(test.full_tok,test.identifiers);
    */
    
//    FSM test_fsm;
   

//    int check{1};
//    test_fsm.create_fsm(std::string{"file"});
//    std::fstream fs;
//    fs.write(reinterpret_cast<char*>(&test_fsm),sizeof(test_fsm));
//    Disk_SM test{std::string{"file"}};
//    Node new_node;
//    Buffer_Pool pool{&test};
   
//    for(size_t i = 1;i<8;i++){
//    new_node = *pool.get_page(i);
//    new_node.print_data();
//    std::cout<<"\n";
//    };




std::vector<char*>vec{"wsj6JBN2ZSD2bjSDZV24","kaHBpTNKKhKrGOgUcGr9","yUOnqc3EQnOoJv8mTqDd","A5F6V31VEskp0jXJEazx","nNDZzzwGPFdUMYbVMjGz","1pEBfs3tHUC1THCY7Mj8","kNyu1grjQyDt47FN0d7r","KByyDFJJD8XN2EttnprD","hmFh4Vf5898o6heODUC0","WXb1oSsmbQv146BJx4NP","f1nyW44eVEeu9QGaQHWb","WQoMkANQSSxWzZWww16m","cF9M2c3y098R5ECgDRwa","rdbAekwgv2c4xjwj6Y1V","fMzWy0G2CxGMhddoUY9Z","qj8h1ero3CHNPquFAYUn","JSYVa7hyyZMBOm5M1wVj","FX5E98Zd8D2J3Emj0Vca","VkAPtW5Wb1s8yurnJmN7","u995dHTTKKSvgmpWEdcU","pE6V1dFPw3ngYo0zVF5J","z1mmVMyN7N0V1R9CJ9n2","Ss3oH1AB6ucjeGVkh4PV","EmG7vabgH5TH7yg9KEZ0","m3PywSyU1YQdA9ZGtoZk","tptznfdjzSvFP2G0xj2X","nzKbAspmjWzvqHy1x8WH","RtECVcQV9qtBwGONMzfY","U6f8WC7mtZCCH6DvhWwu","WpAOO3WSvj6QEsnMrvO2","nTm2JgAW5kfHwg607JzG","wJkAmRwoPKhqwmkqTgHQ","s0u2j4Z4vuws1xnPAQX6","MQEmXadjEXJ9y01NWtwD","kZXGn8JFpqrsAPmZ9YYY","UUAmoKaNYpMQa1S63HUq","xAsxGJctHtmCxYhXNn5x","oYbbxaPHzHCsqPaSPr3n","JwrzPmrYqJ7tB9rtrmEf","HQ0jDHq9qY1HXuxkZPP8","2y11eEprRhxhN0to9dDp","cabAnnoTNB1Oy3wH4pjU","Ngxks61m3QnQ5T4Xuvye","KsaRouYUdE0JJVmBvxeD","V7uePrjkN3VqzatCxnNH","QeY7nSKMDtVF3169Pbyo","gEjmXXPm36z0whuKsRgc","QcbpdyaerCfRyNYSdsDq","B8RNhKoPDU2kEeA5ZPk1","8eTg3WTuF1MJRSMDy2nO","VXBwXPXY18yBDAOKZGgy","RFZjVk9Meav9O2vbasuR","aEfpyhVvSKaw1F9e4oZq","q6fB0qurA1BQs76v0qah","FTG3t1nrupU5uwKo5phx","CGWsvzyRBsnRZUhkgeFP","jTXbfhyQXTwD9u0D5hV3","4sbdc1eWR9D5BbpSgRDB","wowod9tqA7d6go8SaQVx","tzAbkQ0oCqD1nhQUzbQe","4BSE2PBNxagTxTaS0gce","t75Rp4eVgjs3srAyM3AB","5dCEwdtUR4X9UFf2eU6e","NFDcoXjAOU7F3ZPmKeGv","CBF9srm5KaYnEus0pNr0","2rjo2z2jnXp7m9fA1CDZ","ur03V0AHvUcW0MOZqFHt","jnCtE6RX9GpU1DHmDTgo","M2rJsKRyNjfEewT6Jogm","sAoMEedj4cKxvqfnkuWR","ONcCsGS5YZQurChHq3aG","9yd0AawNKxS2yokJEHme","BJ5YGHxaqOHdOydpX0VK","7uXQYPRP9P2bta8D5U2w","9yvvWq8MGkkrkRjqR1EJ","WaK4XrU7DFUUP8d2vX2B","6N5sFHNVyEVcduj2Af2b","EtzRSbso3WeUdcFVmxuY","4T2ou8tYrRXEK0koHw3b","6U4CEcq2k1aRGZhAcE3D","S67AnjEQ7puVqVnx8DK0","tajC0e82C0bNH7BKJZHy","ZPVzJ6cebrmTs8zuvopD","zefDjytxzk4CdfK9Xd3j","ZbbsgOXcdbVtoK0zApwq","C7FyoEBZetFES96vU69Y","5qc5t6fHftowDtskoPAx","9BrgRUrM9mm2jVYTfnRm","kPy67gdYnh0Hj3CwzsOM","TmkYpOBhBP5cAgS1fTSu","kauAz7hefB3SaCnKsSRO","aCH5nVjuU7bu2MCz3aFc","YXA79deMq3qEMTpVOj6y","Psw9TjhkbqxQdVQGeebt","sweBzOoyeHFAocy5CvHG","S55e89su8o4neNJToCmB","KObWOno2A7dNyocNkOTm","1SzaQVJTuvtpwN6S3jRU","c4g9mcHbQwuooP9uphoj","hJyW0KWWMqcec5HEsa1n","DMmrjtjJfQcYnW6T5G1E","5cyyPkUKKNw7H6kJj5A9","E2qqpdtGWzx82XqR8N8e","YxgH4qxfgR5Aw7yNpxgv","8HwW5HqbfGBErb8C5MgN","97Tnny3pAMcHBSoPAj7g","QEsU2E5nzFyfvM7Js2oF","ocD5VvrQ4e6tQw2Gsf2e","zBP5RXPjBz3fKDJnGr7S","DQdhg0mjSpEhD90MXjX6","dhE0FdUYYKGV1FGkHMWm","JwfmcYaUodhG0C4SENSf","h8fyBra6TC7MkwhvBvO3","EMS1jMVs3aJfBMNUfWRM","Sq4MZpUoAPAPnoCzdbO4","oC8HtaUJ1boE4durzNSR","grGwZKGDdg6KeM3WPMZD","oE5cHWEPvfvekuCXSkv2","EOAooCfq7fgb02q5T0O9","7D4CgqrXkasdrpPQdQpp","ntwd5GqZHUEsfB0C8X8J","OqwKxbmXDTDtXsntxuyx","5FH5bdnsfdj1Ar6ftexK","jX0puXgj2A3RXa9bv9m3","v9nOYVmWAAQnWkR4B9XJ","OGBOMgmsODJ7BdRDcGBF","uZs39JrtXr5PeU4kOZWB","TbnFm7HuTgW8BSFEsk2n","Rvnd3v8dF2kWP2s27swR","SEnet09mUTVaa8CtyFAR","oQByN9fgyMYT8SnWg5WG","sOzmcfH4UTVF1Vb9FGyH","pXeQ0RaSNAqa9Ro8p91G","6JXP6HyjBFMaje5cQsAM","NusYb9F5PC0OMftpsTEM","QtEStDCm0zCP0H02JEtZ","CWhmBDukCYGDx8YXeOjr","f6NdBW8uqTeTwGwMbrqF","O8YNqwaPTWQPFqKQrOEZ","OXmOh0emyWjrHnZvMT9M","aRmvQCR2t9cNP9jEUHQf","7pPWTxbzvtemz5OReu83","mMJPbGupV2JeNY4hjmNJ","cKhO4qn1PCbo3KW1yrBY","ufAVoT0BFhxbWY4tNafR","ZwSD7cOARb1WO3jvsPp0","htOsFGXeD5Q11wU0Dxvt","qAXMhEu8EGJD5FPJCCGt","ArnXBxV3Z4bnRpk7TheM","hjcFuBzTDs2YWP0CgqXO","txy1XdRvgSQ4vF0bgG97","mKBZ5bqNzmQhPTzfVqwJ","cvCovvVACjWAp3272tM3","qtYvfTZzHHCwPhRYHScX","Y6W7bHJYjydyxkrQXceX","amOPF7YZ8dqPMoB7qkBo","zQfz3OBTAu1NmJKgKfTk","dnuOc9uuSEhZhpZaVeER","ZZBVHz9kAdtAouj3endG","B7Kxp4cv75920S80w2hK","GVHYKEdJso6AC3wVK1vC","1gSuDhVxk5ec8aoZFnqH","KhVRE8F45rKgRbjmcW8T","ECseRPTUmBWbf1d8Mgcd","yHvq5cDCs7kKCaHQ5T0k","aOmaWhnoDs5dbCvRnnZO","AnSSjkU9QcSsVojZOnZH","bnb8B2jWJYRNfDqHKJjN","8P1YErdSnQMVsnxpsjCU","6ETqW0neGa4Mk4jYjWPm","ZmhAMM64nGq45CGJup3E","8dTczx5OmrYPHk9ZhAq0","QSGMVNuv6w3EnZkSckr5","dpxWvfwUAHC2UMojS8vO","tEdEuX4ZppCYWhbD6PGo","zAqxnbpeEBkGsf30kATY","SDbbpUaMeTqZbd0ruQ0M","W9xS2raXhs3sHY3RpMbX","7y89Gvn6sV4Y7vYxVHkh","tq1tNsMv2BSFS54mpHt7","WJDt388cGu4kE04OA5Mh","15UFgTPmMCabMxoF8Jbc","uUXVCBPKK5V9m1A8QTQt","zaU6svapqCCQy33dJsNm","hgB6FOKXVZ5mMHWV23bM","bJwDAWEYrY2FAsgv3ZzO","tN2UP6vnh6BNJCFsuZYa","UVjTuV7Sa1mC5sGXW8HJ","VsuvbYMdOSucMpB1KzUF","KKJfNwmutRpSFUufr4vO","qDw4pNs4kNuY0Ug0vP6C","KPPBZWz8HYKW3xn8wCmu","6yazdDSXtvcnFr4QAD8P","SnPXKDQXNnDeCACudtCP","kRMen8pZq4cutuxbJuDF","BDZfN4bvNd5aNaWDEn1H","yphpSfuwV4G5TYD4CdWS","QaK92OdAgEFk3H829u3Y","UGu9b5FTykgSFgohKKDC","GFhhaPOBxU5oU4UNXO9A","6Z08E75xFxFY9M3ukG1M","1YpRhv3B74skc8hWhd8a","pckBg4GjCgbb4BNQOvsS","Q5kasW2B5zS6DYjj31SM","zPVmXqJggSm3GkMpc9KJ","joxocX71UApkmfjb6krQ","06ffhxF97QFZkwcjcjDb","XUOGjdvtTHPwrmoWBnra","gpU5W4v4bKW3KnMZT7c7","ABxZUPvfsjdq3J4MakDV","KWbMNbMxUr80oxommGVO","zadXj9PN6ofjCRsUC9sz","SUFPH1cUZjtMZ00SY4jC","SfhczDBuvKH0gRSE95jd","Jg8rPt4RpBoxASutAXMa","s4qAHaxSdcR3ygFESF5f","ZjrMh6g0qR0UQy5drKPp","DZD9YSzYjseoAeMGQpA5","adBcGMqGsbA1MjsvqxV8","XSkvBQEhhzGMOHD1xBN0","MCOje9a3xJr6g9xhRSUW","JO8cm1NWCok97SWo1s6Q","1HBHxyPgDsrze3wWkBc5","wpRkt2VVh3zzhDcYQCDs","eEowtphsWgvg54Wh48BU","HTEuQ4V5fdG446pp1YBS","scrv88f29jBZpK3TzrU1","FhyvarnrYBYpprOR8ckR","jHmO28odG6vynrNZUNAd","q5uqMjUD2du0zzPS7dxT","SOEb7AQgh1XhsjtPfBg9","Bhx2czD3c3CzTpKE025b","kCX7GBacAhvc1rbpDtXq","eP5h0PRnxb29XxXJGCRc","OyGwVROrmTztRMS4wmkK","6D6zGzRry9DoYo1JDy9w","ugUZJzuAqNdyQKCq5oMD","Q6o6ORW3jo3jhb8AJwCC","TbSTCX4O7WEGESgOBrJT","ePbFj59JNKwNaGCKvahG","tQDDMHD3GMaHjyeOka2Q","PBsmz0qRmQctWYg0N0rn","dDsjJmWHWgpynyVY5db3","4QsZNYNV1ERBxHpatMF9","w7ZBS1eoQaTvd7BDTmQW","pQVYXY0dHeDaW8Mc9HCf","vHs1e1BGFUmrgw6Kz8zK","uF6NDbX5zPPy0XTozmp6","4fmxBXJ3cP4MOQPAE64j","KOm7xWOR5FJ3gvK7xJSR","FrKSDyRAeABsXduX3dHk","hMk7aAjraNK4xyg18jyC","PzgZ1qb86QQ2wU1uXvD9","umxkzQE7NhP8Y5Sxf3pS","1CqoxOjr5AFhy7YZQM8j","XjY0KnD9fOxvOEFaXhNJ","XjutDS3GzMJB9nFeja9J","graUukfR8v3zasrtRyOd","4cxogrbs1MWjxDGueeBx","7cChkSZ4mhA4n4feChaS","2CEMt96kMctqNcTTZyhK","PEZGNmGwbVpZvUqNRKNe","3pFvQkscTHsd15kwt6Cw","jyhCoMcJTqaqQyswrnMc","MANKB4gv5qKo5ndaQ3VB","ju9GSNn8MdPKngDT9TBt","wXuHoXC56FagTKjXAvUU","WX8Jun6yx8tCzwbtdj6B","Rqs8eUoEN5T5S6qq4cTO","AJo3vXYkzqUToTuzzgvC","77QKc3APHJGQTxEGDRQF","FG91NQhD0fXjhZbSFvNr","tP01goGZUWg4tvoNJMkc","KHE5EabG5XUoaesyAb24","BtNoUUKK89ZK07eXbJmK","eMJyxEhUdrPpMoFGKxff","SFZPu2AJ9MWdA9ZCwfKn","r06w5CZwRZ56mg7xdU60","ARJEHZ5b0V01U8fqM0vN","5jzOCt3waShhXTgUCgMf","pYjOdr12dUy4tm4bSXwT","UpFtKoHM4BuvRKfPughm","MDU13EOfFeH2FEUAGOxh","9FZMYEauSWVrk921kwKZ","bvaf6HdFKJFYq8hmajtF","TQjC1QBZRHp49pA0zvU0","vGOORevXcWxezbrPc0w1","e6rv5stNVQAKZpzG28bC","4XYFZqCWgKWqdsMx2xQg","oRKOkgGE7YJs5vczMqWJ","OSYKg5omn4MhkhKSjpwg","YpxEMobU4ArZSeJsEhhs","Tn4RKgu4T2tbkWHBA986","K54uPb4cDU5ZU3mtD8tB","DnQaFaXct1EcB4SWoYsJ","CTH1Jkp02x4YseY6HjhG","HhR5jvDKBZqotosZNxyz","axzYEOrcKJNc7GsEBbD8","E6cZ0hzCOk53wgER0Hnq","zffCeGcMOstD7amvZb2V","X4kpNPo8wtH4taFpz8Y8","sJY4rBHGfHynyYzmDMfz","aGrqVeG3BRTrpQMPnnGq","XcAZ4ExpQ21zh1Evvrwv","VRvmbgD4TewQOx1Pc5pw","KKkRgfeqHBGnMSoc9R7x","VuGFNpvBMmtYW0Om6t2t","3sm4uxyXeeB643HWwB3F","D3zpknk6zxrOVmE7FaMK","tUGSG9Uta2BROxve8uHT","h4uEmHsUkTsc4TJepoAT","HOy9vgJ4RHKpYfwCX2TT","rgTh4ZYXggxXJROMypwW","ey2uUA7MZyRcsetW99Ow","en02zOQ1T5jASBgQUrwY","xsXCwscN9dVnQagywhXN","fAh3jMOQZSSQAR4V9C2O","91SRUogmPV5p0JgxmzZ2","K1M69hWh8yQkK7Y2DMYE","JxYV84k2v8ctfYSeKamH","sW4hTcre8wzAMJUWfGRw","zACntNOwCdvWXCPmJmx5","ZuZWsffMetj1yGdwe7xN","9R9ZcC7cObxEwyDJ9Qhk","88x60SUnySWvPDMyee8R","fQWKOZFWHEpoPfnPMf3V","5d55Kan8EEcAxEfKnNyW","xBmUGOYwv8yAxeNJspAn","1H6cjar3UqysVkgWpQDr","9mUYaySqvaU8Z0126u32","KuSucDZEkDMa8mtSyMfN","mQVmXsn4cVBGXxF2SzDu","VqsjOpakcYvNwV2xBMxK","bvdkHxVb97AyCkq65wn6","p3nOhPhTtk5O51voAK1X","4ZWnoxem5a7YBd0Fa3FQ","7snm4SqgwkVX0ysdjdz7","nuytDOd7vWYaBhVTgFT3","z5bMV7WhZp0cmTPw0zYy","XX4gwZrzwr7SuJ2WxV8X","ekG3TKJ8NbjaCK8QbMJA","tEdE13vFfafjdaNWnUvT","pghbk2O08u0cWaeuQpdQ","37roGqQZVmfySOptwrKQ","1eJZvEeENVDa7BadfjVm","NNRxRRNCSjPnA6SPtv0O","KPgzAO4ZTUOSzEdwK6B9","Afu8mzAf8CPp6Yj1gD0G","pyUHmyGc03SjDdYCrrbV","5YtS4uXZG6C7DVxNU6Wh","Ev63DUPGH1SAA6DAy0pC","Fj9hwVa2X9fc0rqEQQg6","6zf44HPhGzMrhRtzuFYw","sHFTMsj1EwwMStzOREqt","0sv9jsRggWvXnGMk2CQg","whDKmFBAxURYREAHsukq","NuaT2uefvu7tN3mbn58y","09jkCQSnmPkBaS82HMYh","SxHYnwyQOxR488q2AdoA","xVzVW9VUVdrRGrfEVdBq","Ek5hbpvyrW54Xw2JCmdP","CqFz0eEKMoDhAd19wn5F","0HzbkjZqfu5eu9ZE4fgG","dD5UATpKFMndEBMtd8be","MXmfT06dEXtQTeFvR3wQ","zyxgr9hvrzVABuFQPaQr","QN91J5c7oFQ1v8VyjyG1","UXW0RO9CtC9dBXaUAnWS","hucACvxD60e1jqqTn7NY","mh3gsn7wtxxEY9WgFH8J","2Ex1eogEDPKnj3jdQoqw","rSg9Qat62VxO9xFE9Dye","nQfBtodUV6A2ca2hKbJs","PdO4nWRnpMTM8CdHNHcn","bAgE7TjCK0AJHyPgyWjZ","xnAdnM8sURsHpQp2c243","63FSeoGCt7VXoDydxgVy","pCxUqt7nHuMyDCbTBZ0x","DuD7yy9UUCVo8zmehr00","ktZDo7yxshPUzW00ueU3","fyFk2MB5pgwUy95dCCrd","RT3YAxN9WGo94B7Cbz0C","kFVmq8CpSBRBEY9AdeQV","tG2xY40uOejnDpR7ffuQ","dGBvTKUUYjUVDps3psoz","wCeYCV1sV1EGrABcYC7f","oBOksQyKU8F2nFV2C1db","tT75BORJb0Sq1n18Ey21","RTujpyXrmpUVc8XTFnqK","J91DW70nk1xoX2Aaqdmk","F9YM9kZ6hsQmpgsFnKg6","3XXsxG9Z1M9109zXYbKH","eqamPw1EhKEYNcNfvORD","bABZCbuey9dpS3GBgbwj","JWvdTwUHXmbGZqWN6JzJ","p2NeKjdKzmeSpouSxmvZ","aZ6CBQWfzqeptP5K09bU","uw2K5R8W466H6DB2WH5D","1nsNhMjsEqtoKmAOJuQ5","yUEXxcyrKBTC54ZBCfKT","QXrquzBTezGhKxewK2Es","WVZ2gGA8zM4PexAQbtCD","KGCbRpdKrDcqDeEkrvdh","b4v5BWhXH5Jd80xwEHp8","FtcwroOeXnY6jDCqWX5W","9bfUecgQUMaTSgfY0wdo","WnpK0Ze74Rwf0mA8Z4Gc","kyBxF3xAUQF1tFbSzuYx","9VjNq7dTavQYOAuwj0xH","DA0WOtOuEkVk0J8scx2m","F7uo2WExZFnHmqugCNek","hTMuzqcmQ0HYZPBS4pT1","Wqgf7GrAbuKUBbSaFJfx","TWUYS2ZOt0wMzxUjRXYE","YK6j4dHnqBnQrAHpQagk","h0Zdy1TN281QqFRcRy8B","B0xG1EaqDjRaxOvGB16O","xyRJGJPM0aCc3qcQtnJq","Oya3AceD5GqJS52pdEBr","cRbEWa2BDa5APHC0RQhn","oRMpVpnyEJr44RMTV1FV","dhKtfUrMWcx74RbMDTGe","0jyQhXOBhaGxdorKfwJA","cvHMM1opYYA3M0WKCMW4","yMkxqRyq5mpyhvBXFFef","h6hcw7PRChnDwTDUVyJx","wuBQ6O8gx6Vn6Y8RXo4n","3a6QzmxzCAAdphAaACKU","oQDEWr8w5VG4Oz5N6Mbf","v51keh72ECQ6bPA3Y1SY","gcp2tfk5WagbTzbqM19d","fndW2tyom0fj9BNH5NmY","Zdc3oqXOkVEeTOE8E9fr","FcY8cv131fDahMDSbrnH","szOkvwKDjZ0JmvGqXBdM","pyWvPAA6KUmhjkVU1NwZ","XmRsHrxRBaKcu6yyWXSP","v9uq6DRfsHbsK0kFXEBm","fV91Ut675MNvuV7vPBdX","FryBye3TOzedcYrWZCHG","6noHF2QwdKn5Zf3QHxgb","ckR9kNt9p0SWmgWS9qAo","E2AQZWJD0UVA7hSwODby","4dQSdfytXnHCFOx4aY97","jfAQZ3R5D7p8wFOMawpc","5rtMU2UkXxyQZPCXsr6R","BxUUc4vBq6NYKUNemgHF","Q9utepWcoYY06fJ4Dt2g","VSrnSQcoRkjMrZKH6xPq","7SORAzGfCx2fjwEGaQ2e","8avR0S618DmuToFY5Tud","TPsoy7pDsK9tMzCA2Srw","xDdYcEJ6EocgC9mt06QM","JJpUVrzmVNTX8uZUMa0t","nCu3EHrPhYHKfKysrx34","hKZGcoGDpM8k28fmsHJO","tYqNNcVG7EVeQYUWYY9N","yF1PtAm1m9p22O26cRbK","9n2zwkSVFZ2orNBvjAkf","rG7u42u6nE9Sg5uD3MsN","2r3ekqSZv25XP0pfAFHa","n4TDPxmSGYNuuxXxzpN6","xvxdXOAHC2GrPVyj73QX","j3vM7wg03Xg9H3Hxa1PY","DEahNGnpH4SGV1s94uno","zpN8EYJqsvcWUC5AkTUr","FN9JdpeQ1puwUFvX7OUm","r8t5M1BB77jEKdO8oRHO","68fPwcGmoARR5qJYjABo","t7aeK0mRBoeoq0xG11Of","ZPADHRZ95yCPjmEGmer8","BqsS4CQp3ag1Qt5Adxw6","X3s2vkt3WaOdxOKdvS0C","mqqWXAboEDQo00QzOAoR","fP1FwrHVzsJAGJTu6Um0","5TzRnk3caQOjRVcGRffC","b16X0bR9A3rJCA3HDS1s","0Gw1XmxynNba7RcmjcHY","MXMOuHrqXRwHURqtpnA6","OwA9os0zBZqP2ubX26xk","s4qdF2A9jG1cGSRmMh1D","5TQSJmSWUFvgTzEc7MGw","NBr7EX4NFxtXfbn8cadB","n93Kmu4TP9FUDVaPp87r","DApNh64YBs6O461UHBt2","dXV9AQXP2jC2g5KU4JrM","MvTfAjv3Pf91Km7N9DKv","ya8GGDcRnad4h46yDoD1","pDDUzAEeOwODWrb4820G","eSjxN8Docc8YxR5dMV0f","Y67ZptQeFEDRasFKe0sA","B2jVPeFsSTcTeeAK4j3P","2ksjsX49gjs5C12FZTu7","VUOpVtfVtmJ0qwUAQAOH","Kv6wAhv3Gzzd3rRE74sp","We3A3G5zYw4mUe4EdMHo","qJ9wAkTWm5ORonmsGgT3","YYk7zvaQwbDZO1q4cYDy","aAgqjOqQBfpJRSsYOn0A","XzppUCQRGGqpCjH2O4OU","XGcRYAV68Yn52NSsDBUN","F5bbNQMAHbNqM89nBPAJ","K9FcKdZUudPEeBFEyQ3Z","7948y95JDsz6CH0ueEHC","ffva2DcKwXUzKQQGazUt","zUxxkSMRBc3wFO9PrpTb","SaWpNf92jQtFwNjgmZF8","HScYBXmroghf2WwozrR3","bHKy7bSSvNsA7r8KHryJ","rdo6W2XyBkU4zSE6HAJt","5fmuJFXBUn8r0ZUJYf8y","QCZYzuskeZj6oZZ0MzRT","AfScEFWpRAQY2XN31Pqx","sVMTDYd1B5hMdBrw0Pha","SognCT38JT44JEp9nNq0","4xHH8St9yxzekRgn55Ta","kVJGyBOmMT4a748NEA2e","gwVw6QPV5Rp50UupGfCs","SBV0KdtC6zGVMRSpTZRE","7vYP7mf1KVgVgpNXV7yJ","UxYMFDPVnczOcKVHzVVe","1Q2RABtWTmAeMqK9s67Q","AWZCe6ATrD7zMqtAMTUG","OuSEnUXWqV5Av6y0UE4O","wxCo1JGkUmGsHKaNhw4W","aTd1hSxDyFB5WmkFoCYx","MXFxvZBGjQXBrSfBm1Gj","JdQV69hks4462GT6qyfv","g5BXOvT5ezDS7G4WXKZC","Pm8HQQUqR8OzPyENRDFh","t4BJ7jCY4KHqTPCofK8U","vHwAejVGd1ANTodtZnWR","TfjFdxkJwTdSAN36q2f6","fkpmd7K2cZRO7PjHsWyw","UvhSRb6yeDnHh4mo2ppp","nW7m2ogMJaf9z2syBM3t","k9tMqfjCgH1OAA3gaUJp","gzPhNAHCJq4081TQHXcg","fJEcAuYk1GyHD44yeCN1","2QcTDgq6kMo90EFsS6FO","E6T0BxY5ECTBzrrMGtz9","odTSa0aZOPR3WJej19Eq","56X6XKkFmKeg6KKepzZp","7TS3kNVfVoo2ph4U45H0","KW66Cg0mrk4QnZXu1ZBN","fv9PFVEbwFsVUguK3Dej","WoP9h3hoMzwAzSUegS1g","xm8MDtGKs1CgJ09AYRzd","NuVmdjzOArqXOA2Mjvxf","1sR6doeN2yj4w82SuVY8","u1XgKo8musjN8WFfeCBD","O1Ng8sA6kFPkAtqZcoTH","AaqS5xU7GR1CuFfo4tvK","s5ArEQmuQsoQOtBkUEYf","QNDPHt7Ofr1sbCq0X2VV","cvcGyhJaGBkVm3CPXpm2","AGSaV04cG4MW8sG8Y0qS","xr8gntSWTzWHnwjOt9nQ","5qrnhuM3VagmXZabmf5p","vjuYEkVnswmtcuodjae1","4BDnZYTbJ2mJPd6vjKBG","bAGBMn7WcSbNf1hDfTnC","Zcc4HVHq3OYdopkJVTfs","WhUpOFCWNYo3uRfOkrQN","sE7vVXQ71aT4Q3s673uP","FadVBcOJz1WkmSDjKu5n","GJRtMhwN2BywqaDoARx3","7xETE6oCHcDywT26PN5F","6wjMZWnvuSCjCyHGsYjD","n34J6QtESoQ1jwjNeYAC","31jYHRqwwr4c6dg77n5h","bvDX2yJNNBt2mBvqFOem","ScfYQV82VAY1y62qMxG7","UP5jjdcODWUW83jrxqcJ","UN9FwxObWNS00bDSZZeq","XhwOAgT6BYxfNOThKYHJ","6oxjHt9UOrf93r7zDmEx","kmg9yVzEsJWSyXnVSjvw","U3vjR2dZM2fGUzC0V46P","FTbwQMPDvwBSbFVShndb","0EDNTDRh72FeG15EoVt1","kdP5eqDScAka8BEk05G1","Nq1tf7KfjKEWpc82gnyH","Humfj3h8BVWkCJtEnH5q","RZzwQFJreFd6JHmBMsX2","waZdKxRooJ1VhHxyhSQt","zMuQ1yHdkkPwJjczK5Hb","hcdDVXcOBoVYGcEgtyNj","oGctYc8Xah83TCx1fsHS","DJBnADXtoFrQtbT5XBVx","uDDmFTdacSx9ERcVKWmw","95a2T77wq4Fwz52ZETHV","4gu6TdpGsoxFg9hyGQrR","FkAxzf6VkrOdKmR8ok6H","26bBvoHVj3WTVyDKaYds","HuOrbA1APswg61vQ7nSO","FNtJspEaAE6mR86MPGX5","t3A7kQzWsvgFWWKE5MKO","xvRjOHDYEjvchxCoYXq8","eDkXMUyTew4RzkbWwhJz","FJ5rpzqv42YVR19ch6Jm","zjrUzyGsnKnJDvbRqzA0","XzG85Y5pAqFTr4PDOfVB","qkEQqcP5S5Qffdxb1HNd","n0s9UMZKshJFwVG0AKU7","zJAdUfvgaO411t8XgcEY","JOg6UjTFeUOwThyHTYNc","efZ8Pn8vu9E4j0zZVxFd","uZ7YdQC5CKy37Fv59dOa","WzqUMV7dkRjK8VpbyBG9","Ao6EsGf9tQGGFh0OcHQm","wUO5Ej1RJFDh31T3vNQW","grbhjBEUOQSbfejbsNn3","vDUpRAh5H55UhOWcqUjx","AN2fCn4qVE1MaSVcWEV0","7CG4goNPcGzWpshKACCh","wja5MuFpnGSPXs1souGF","SN5e7yY8BO62H58NC6j9","Gd0Qu4S0xnMD0tr4afef","cHm0cGGEgX5GjQKQApNS","ZqYUVfWvp2fbFp72c8AA","E4rW3xUjKwV2tTOo2tJM","EB4EWjbtW2Xe4qFrwtk9","gvZakkTGWkUyV601zd5r","fQtDCZo5GtYWpp00onnD","kNR0xPkug4EeEwb37XnA","muzdYjd8UYTaOomE0BfM","5WP0BWhaq6X7N2soeXgK","kJcFVogNMuKdvfghERAT","xfKA7CvSDY4dDXxSmohc","Dbxzd8x1VmefvWFbz1bQ","k6U5doYno9QPnYr7oeRS","2f2GZvXfFo7nVxHq4Qee","mpkX3XJBE3GcbGHUXb2T","mptNyHsAHHXyvD23BbTB","6CQ7MBrmWaHopdZj6j8s","6HyFyeeGtST2s8ZZtxgf","y5CeoA5VdnzmUMbZemy2","eRcB7R7TJcWB0npqAQKm","x9zwkHk2Uk5ncfGaaKNm","bJDEdHmtHApTJ6cjtmPS","9XTazpvgyPwmBOuJXHcM","qnBppTnTog8WZb8AG37j","6DPmDzdd4WbgHJhD2m8H","tsjwFV6xcD00Q4SjShZw","e1avcHkOsJDtOnGFOTcR","F7sF4SrsRzUgxs6qF4aW","8KEoDubn97rKxZzZCfVP","AdAOcKkyJNwny3WQ4r72","uwX57C2Mc03eRWn2PEAB","C60QM4ZPnEFbVR90dOUv","mc3vR7HR4rqEGpOcr8Kg","FhVV3pnScH92rUUt0wwd","ESpyor1N8FgjJsEE5xc7","mJQR22jbF1WsYEtDyzTk","MeBYV9hDE1OmpKz38Sfr","oPrp6UatNJtOCxoVT8Vt","1WVZqW1dpe2xM3akp808","EktG9zgKpfbrMD8GESd6","VDV8Y4j5d7V885mHfJ9r","hg9kRWKjPhXEw7q8tJVg","PkY9DVcWtcX16p96vbEG","tqSeYevvzc36z9tED02Q","P1spkm5XsG2b8HeyfB9z","yM0gsfPGXopu3dOqnQQ4","zvKuXN6F923xGNahS1F1","31fSUT6xettdQEhUmaW0","BaADNXm7J0eFPuPsyPk9","e5F3fkXWyADeWRFgqEck","z2dkHF3Y3NAYhqcXsRjf","8o5x4HhPYW8Mru0h1yoT","1geUTwuwUXk2GS8Y6RWQ","ewcO20CUAxCR1n5QQzsD","UWmUh03DJXySWPrDrnjf","nhhoBRSvqP8D8XJEgxOO","hZPQAMPOU6Tej4Bxgk4r","CBhwMnwVEx5kxE4qoPxe","6anSUJMXJGRCbpAroNY1","aPQHoxa7XtHFd89e6nrm","H20cWVWmfnVexZt8kyyf","wwmcOmbHRuFmFtMTG0SD","Sve6ZwZRprwufNtQy3sk","A3WVFTcGUdEw4OQmY5rJ","VX1yg5SesBW2CHJT0NMJ","Z0dOT0kfpeHVEUoSwDB2","ANVMS2dJ6BRbywc2oV1A","ThgvU6DyKwHdedT4eYZP","f6MOGCUjGnXC2Tr8bccK","Jd1g1jy4Wd9J6daonJw8","KGXsp4ropCKAscGCmJKn","0XAJ8n7xVnSVD81SKcty","CWQxZ2U0d9Anpy0pxTXu","Nyyx8RPZSV2EBQ2ASa41","sJdMzpw1ez6tHmpw7H44","KJ9CzBxsaZU6oSe2CGUZ","XXaNUdCCyZrVmVMjCp0B","J31BvSZ4Z3M33FdoUCKD","ZexYXJnjVvVDgFN6HPWq","9YyJWjjTdGTME6Tb4u4S","U8ATMDes9uX2vdXuFmyK","wO22z7ewoqap5Vo62TMZ","BYN1a4TRJcOVXfJVMCu9","A3rSKR02BAJ6T4F8Vg1Q","e8Zbjr6Be8uepT5OYF20","4ed5po4T72wqZ8bBZT0k","O0Rf2jz638y7U0cM1bcg","sSG4QU4vHsW0YAJK2Wrd","SUhKdEB03K137Sjc5d8T","SKo0EtO9odDZxRSH4kHJ","sjO9HG6NbBPj8UDp68QO","syxezEX8wCaRo3uWXcGP","n6BqUEFfCp391gR0oJ3A","QXhDM11Swvz0up7rwTJA","mvzctJSNGE8VOmwF3Abq","6O4GtBTYC3BbqcScpHek","xWh0zZaZ0PjEQhKep158","uPMG2KB0fVqy1bvq3Ht4","steBJ4VcSKo1bJU60EuA","9S0oaTPPQAV89grxbXNs","xsgtwdsFpkYzV0UbAbqy","PaJrh4UD1Uh4kmcKjhGv","3vOWwaheaCoyxN496Cad","tuytgR2pAhjTT7nVnF8R","3ocTgkcTcc5eot0Aac9v","RfH2NyAx0DrBbjmE2xPW","f7OBSbbEpqrFpqgTPSYj","4a1Y1BPMy2mPR40Tz96m","0N8ycWVfbuhbVyjq4ntx","1E5P6eJ8v9oXMY7vk7NE","Thf4xWJ0B9egQ5OndTYR","kmKyp3CEMaBv1N8jRrue","OHSzzQnvxHzfV9o6htpO","wHGzAopatRaJBreEfv0h","hNMMDMaGvDTjmcZc8hGG","xXH3ogkV5aS67k0z5auW","rEYmMXq9oE02E7A6DkcR","maBAP1JUdo6HJgqZDEuZ","kcCXjYuRWo8e9Eg7nSUU","S3un5wMTNK2kVOWxwBjO","aw8HojJN2YX7wZhguKdS","Aokfxxg42qswChSk7XfC","pYKNnNgCW2wjToRZ5H7z","qqENrYqHTDRfX0VGEn39","6JjzOkm8s7qRE3JG0GyF","6PgpwoZ7hBvNBbcPUc5V","SRJbh3J9dOpkRxx6z073","C1j9RRjOxHSsuW6C5BN1","vqFBO7mxopW59qcaSXBc","asvMzqrO9HmUcTUYKHuf","RA0SsVqKkUDRxtZSE3tS","A5XTABa1wRZ5avqfE8ym","ZCR1S9sB3RKPxv8fSBuT","OAxo1Px8NZFYjFq9jERf","eKoVDRUoE8Ko2jMp2OS7","TBRj7xwQdXrg2wMqokK2","mXU60UGmDOZYAgGQ7MuW","Q53uwTvC9dzBKcsu43df","3x24a6RtMj4STC5YCy59","58uRNG2ooEuccjYeyNeA","xp7VUu5Qyxz4cN3FKRub","UzDKZSEs9MZgrXbC8N36","eZoveMt5tsG4mcQ83UZK","qS876rVvaj1o9jzFQuCD","zv7G7K2d0m2kOnZP90J3","BwwTQzg8Q7mE6md56wN6","003jMD6tn6dgtZwqxXm6","aX5KdxcO9Xpnm8g9ma56","kNOYC4Ua4D0jppHa0JzP","E03MqvQYrwbXsx0aXbVf","pYR7hDTZKOe5Zq8zWU8k","o1mZ28davzrrm0kxGQOT","xWfqvSpPvnE3xw9duKBt","cJPHbSdWmRjEVgmWCrZo","nrdhEE2C23088u6xcZT3","KwWF79CVE00HNypjZhsF","7g6m8HXQWnnYYSeAkGeW","ZwSPvR6DdXsA58Fdd7tm","wMqFSms2GbbAu06eRcQU","1Aqgwe77zzmUq2mgS4sn","kPWbMzQMWQyHzHfjZBHK","RrMQ2Z8bfJjFGDex0cqN","gYKprNXoJy8fXASOY2Vc","prcpFCjeFSKtWYJFwduJ","ZWjut9BgcFtGbSd9rSV8","S0hS3cmNYy2ome7RzRCu","nNoncEfMr8F6jmhSTTZq","5GaUP03H5ESGtTO5P5vT","zvKGBaDdrSDeXMRPny0d","9pDQSur2j1xSYnj1ytkq","WxUFwjoBVoE4dTt03jdB","nxyVtjR6daUV9dpBNh6f","XJkV8XVS02gOHN0G7gtK","RfsH4W9F3TfZMeot5uJB","Ky1ddsW3Xtuh1zYMyHDp","yHrjvj8ANfqkSrGYjUAE","NVnfqCwrfdKkNJu7QXHo","6ch3JN0Sc6FFOOyCJgWt","5Vxxpubh1dz2ZE8HAwZ1","f9hRqnVMucuyzjuXphFS","xSV469d5OR33KZFuwaPR","10HcnPzeMjaHVV4kfTSN","gQ02U52TUj3YMaUpcqEG","Bwz14DXssMk8CTvF1gf9","w0jJCVF9QSb34mFJKPh6","0RZF4fVMgsF0zy9NFwtT","xeWrxYmSKbXWu0JquanD","ZRnev73veJEBQs43HGDf","e3t4RyHyhWPgKyWZC5xr","rjyMkyazgWkgAHProvsa","XR046O9rpZot5xq4gWtk","gOh3G1ncqAwaH1sXZxAQ","RQpDMJwQxtTab9d15BGS","Sc9jTq56v7HvhBjvAYoJ","3EkSeCBdEsttqhts3qs1","Oa447EsAXSKo4deMaJ3U","NzPRU4UbdwRYFtUHGVCM","4RfXgcgAM0wNQPM2rdB7","trNkptsjcaEcm957EM3H","rU1g7o4XvpYeOzue3o6o","3WP3qjEaTuPh0z4ooM4o","toSVAY1KggM2dBSD3ySX","hbFqE1GkBUyJUNX4MAG5","gDrXjyY3vAE6HJ3RvKbx","d79MAepPrmPnoZ5zZPhd","Q2UvdfdtXfCjoSRrrWcm","z687wwNAgZ7CV80nZrye","Zpnq6OYozReu587mah0f","GoBUEXeBnJ2UgaM8WKkq","Z2EDRMJdruvN57gtMxmm","6s6JFqkjUvQ0zb6fBT7A","F9vaCMDdKuxm7sWYyxeW","t3XQxyBxadfVBA4KuFEe","YuDsr8DQZrs0OsY0CtnV","7z5rxCXoRwz9koU2pgqh","N2rtQV1110UBamDWF9nk","zMmDoeMZqvsdch6x8kKr","zJPedVPK1Fyw45RHZEFN","yFX23CdGNrRONuAdsEwK","Vh12wwWvrdOyjR3jou4p","5qoXCRusf0kTGU0cbhk7","y5jFRk0yfoubT0uU8uKA","jGUgyF79DG0j1ZtZkKxW","9Adxm2mAO19yk1Ac7dYC","ycR2mkatYJjpO4eFSMsa","0pAfA0wv4dwhZoZkcpm0","FTnD6wpCogJkVXb4mevC","B5rGucVcSD7UGvV0pOq7","FmuHAhKeqQKA4s6coFx0","EJrRwupG47N945KR9ka3"};

System_Rel_Row row;
row.kind = 'i';
row.check = 1;
row.num_pages = 0;
row.num_rows = 0;
strcpy(row.rel_file,"test.db");

row.row_size = 8;

B_Tree<Syst_Rel,System_Rel_Row>tree("catalog_rel");
Catalog_Rel rel;
// rel.create_catalog();
std::fstream fs;
tree.info.fs = &fs;
// for(size_t t = 0;t <=7;t++){
    
    
for(size_t i = 0;i<1;i++){
        
    
    // std::cout<<"I: "<<i<<std::endl;
    // if((i+(t*999)) > 7500){
    //     std::cout<<(i+(t*999))<<std::endl;
    //     if((i+(t*999)) > 7664)
    //     break;
    // };
    
    // strcpy(row.index,vec.at(i));
    // uint16_t key_num{};
    // for(size_t j = 0;j<20;j++){
    //     key_num += vec.at(i)[j];
    //     row.check = key_num;
    // }
    // std::cout<<key_num<<std::endl;
    // tree.insert(key_num,row,28,i);
    // tree.remove(key_num,28,1);
    tree.search_range(1670,1765,28,1);
    for(size_t i =0;i<tree.rows.size();i++)
    std::cout<<i<<": "<<tree.rows.at(i).index<<std::endl;
    // if(i==26)
    // break;
};


    
    
// };

std::cout<<"done"<<std::endl;
// const char* str = {"1111111"};
// strcpy(row.rel_name,str);
// uint16_t key{};
// for(size_t i = 0; i<7;i++)
// key+=str[i];
// std::cout<<key<<std::endl;
// // rel.insert_rel(key,row,27);
// rel.search_rel(key,1);
// std::cout<<rel.info.rel.page_id<<" "<<rel.info.index<<" "<<rel.info.rel.rows[rel.info.index].rel_name<<std::endl;

// std::cout<<"done"<<std::endl;
// fs.close();
// uint16_t key{};
// const char* key_val = "hellonn";
// for(size_t i = 0;i<7;i++){
//     key+= key_val[i];
// }
// rel.search_rel(key,1);
// std::cout<<key<<" DATA: "<<rel.info.rel.rows[rel.info.index].rel_name<<std::endl;

// rel.insert_rel(1,row,&rel.info);
   
//    test.read_page(1,&new_node);
//    new_node.print_data();
//    Node new_node2;
//    test.read_page(2,&new_node2);
//    new_node2.print_data();
   
//    do{
//     std::cout<<"Go? ";
//     std::cin >>check;
   
//    uint16_t page_num = test.write_new_page();
//    uint8_t hole{};
//    if(page_num == 2){
//     std::cout<<"freeing"<<std::endl;
//     test.free_page(1);
//     hole=1;
//    }
//    if(page_num==5){
//     std::cout<<"freeing"<<std::endl;
//     test.free_page(3);
//     hole=1;
//    }
   
//    Node node;
//    char str[MAX_PAGE-12];
//    std::cout<<"enter data for page "<<page_num<<": ";
//    std::cin >>str;
//    node.set_data(str);
//    node.set_checksum(32);
//    node.set_p(10,11,12);

   
//    test.write_page(&node,page_num);

   
//    Node new_node;
//    test.read_page(page_num,&new_node);
//    std::cout<<"wrote"<<std::endl;
//    new_node.print_data();
//    }while(check!=0);
   
}
