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



System_Rel_Row row;
row.kind = 'i';
row.num_attrs = 1;
row.num_pages = 0;
row.num_rows = 0;
strcpy(row.rel_file,"test.db");

row.row_size = 8;


Catalog_Rel rel;
rel.create_catalog();
std::fstream fs;
rel.info.fs = &fs;
std::vector<char*>vec{"ggj8qvO","GGExUDS","PYMhmAB","TQhee1m","ooT62qK","2NOv3aR","qqnsOV2","Vvzvfa7","XQsc9bw","p4KF1k4","0B3NayU","ZHS2HKb","f4wbpp3","dkJtE3d","rn8qdJ7","pJ64dgJ","ANqdzJa","vnzS9hS","BvG6bG3","sMhPxq7","MmyoZfw","BehfRxO","5taf29H","4tOBhDA","Fb3P2PO","AjRRkkV","cyc0tMv","0U7zuDO","NbXW1hD","S2axgyy","629N44M","r8GAtwr","x0xMNCV","Jms6t82","Bn5XSuO","avTP3Pg","cr2sPxu","n9BwgCo","uFVMJWn","j69QRmj","hc0nooe","SYxrPoP","ebcGJhO","uK2NPgH","zg3Oq5h","0D3Pq82","Sm0vnaP","8FVKbQF","nNKKRvA","7VGAwpN","PRpCc8r","dw5gWAW","P7uxpGM","mbeGVXq","Ermb7k3","v19Pu3O","ApE0RVG","cJAWRtp","ypDw4Qv","HmC60xJ","s3Gdrcz","p8XyOr3","PAn4pvg","HK4rbWZ","hr1qpFK","nCfkNSq","UG88Hy4","h9DtZwQ","rvu5w2f","cfAn1w9","pCAC7Ok","GFCug8B","96u0Mqh","zaB3Vc7","teYhQgG","2p4zn5g","gBCO8DA","Wp6uJY0","rc2Tqqv","a8wFvfb","8ofs43v","hHZ37Z6","YcaRGNU","NuSAvyh","nBFchyC","uc7XGjg","3SMuf6f","QfzBGpQ","d1Sqokn","xg1GEv6","ShQnuYr","bskSaEU","TJXgpwF","rkGJXQS","K2QroXq","YPPs4En","k0WXVyA","gsDSWv5","hWaZQWR","VQzdCFw","9NZ7vem","kJKjBAc","Rf6K9K2","wmxh9fm","RUB2kPY","gwn574y","wTyEyfJ","vCn8aGR","kpWGxXo","7gwpmdy","pkVXdBU","PcSZYt2","QMjBXee","KRWZ3gU","ruQkWjv","4DNcYSf","gZVF4FS","rhPRgWg","DW0kSsy","jTCsnfR","A5F0A2u","MV7YszQ","9UkMxbh","p9w7jf5","ofyA0Nc","ZGCKHyJ","AEV025U","PKsTB0Y","8Dmz9Yh","t3Kz9Qo","aZW0vUP","DXY9qvW","cd3WEKk","khkSpMP","459mdhr","Sfh071v","fjRraFO","UKPAnte","OXwaDdG","qrAkb8B","ydevbMp","E7Zmgcw","J7f4SR0","6Rpcbcp","YGjoccu","anrdP5m","Dj61nVg","M5nDYxF","3OToju3","ZgSZTKT","te293n0","fPdsV09","4CSh7qk","gtWRzfF","7Xx3vqW","h4e4Onq","AYqjpFN","Z7cHGbF","QFYKz2V","j1EwmMp","38GQXwU","WfqpGQM","pUde2Gb","MZU71ff","XGCDzZw","RQD26g9","WsUSPH8","tHkhkjU","aaSZZXT","0dE2pCV","Xyyea43","oSs1G8O","6FkhdRK","kGOo0eG","qHaRZcK","qRYBt7S","6sv1StX","FC42C1O","qf7kJjA","5Yo7Cqd","Gg2VNYE","B39mHqj","ACBB16f","wpBVAvH","T5B9GwY","4g6xaYN","yt8dJC9","aqny6Tn","zUkfXGb","8jz56B2","5UPAw0y","baV6dJV","bKRzaP8","ayzyaag","RS64z2r","cavDH7P","WKR95kK","4ty3SEF","ovTmsaQ","cDhmTte","4nqpUtw","fSTkOZr","QdzB01m","oszn1m2","cVe6VFx","xb2CcsJ","GqTBbnF","eaGynRf","9tO3zbG","heUDnuT","hZ2W0Zo","cb8AH2p","fJnO11W","oz0ue74","1Q9cfu4","6OvaSFD","GOqOK2A","HBco9EY","SAC2PO3","WSmhAHQ","KmYo2oA","uOogDvw","yvZkXN0","EW3AcU3","wn30TzM","VR127hh","s8fM6XZ","z6cRnrb","t6P5X9Y","6r7ZTVQ","wdomTH9","6JSm4CR","ZjXCUJU","rHWBu6C","OmMkc34","dxtJefj","qwAO2Rv","zC8H0GR","GGdbErM","ake2jAb","nVmgu0v","QSY894U","g64hmoe","PHA7Stu","dN21hAs","HjExU86","58qO7DK","m4VrcaT","0hhmZZf","UMbGKux","qpyaJCC","qcA0nWc","MMkEkn1","xF72N4v","dWhYhPn","DTUKNYf","JmtJMMv","3wkjwh8","4uVgt14","4xmjG6k","aKyzH9T","GBz8fvN","V1W2udz","kfY4Pus","UDdjkKn","Uc47ouM","7cHGEyd","3AZzJF2","Jh2QC7G","n9XmM7q","zGeVKRb","odpzzg2","kUvESRc","qhSkKHh","MsPbQXY","44eJmU0","Z6eNSuR","v7DV5vF","xfwJDu2","mY4XoUc","x8arteC","5BhTp3r","oodwDcv","mmQW7wQ","kutasH9","JF3WWWf","KbqrAOJ","KbN8F79","3b8kyE8","wAO6CyJ","hXd5xj3","1OF99dm","hbWk7t3","RkmDVV1","0jpvUnJ","wGPTTFg","nX8o3o5","4SwQPJE","6q8YWoG","CvQ4jbk","OmnszHZ","5Ck9Osv","wfRFHOA","VxCsUhH","bUcuau0","QDwezzo","xqeD5kf","wRvgoS2","7qY43YF","fkCeOyO","n3UBEee","E2xsTOS","wtPaYVR","d6jk4QM","aNCb7Uq","SKEFVUT","ztd4oQ4","OtDH4gC","WCxsRNn","0xtMDdF","qyxKWHB","OphHY24","n8UcODx","EzGD7Mu","HrkbP24","2fCEkYC","24hrE1p","ZAJ6m6O","hQh3egS","TpvdSEF","g00o8eE","mtGMbZJ","xGAJbbu","x6J7Oug","OJPOSxV","nPhyCnh","smvtuau","FNMgMh8","kZwDXUc","10tYkGV","z6x3FPV","fp1hCM2","FQRFKTT","yP6Jz4O","dzKSQ0q","E00UY0z","8y5cZjz","8TETtv8","VsnK4Qw","7vm2jYO","2h0ckfw","xCdxoV2","5U24JGP","35xPOC9","ocHtVFe","AHw0sVq","qnWy17K","vwAGOQQ","2uReaOr","9X6gajj","OksB9YQ","URfuvr2","P7akQM6","ryhotdg","jpCmq1N","MksUmHO","k0D3MDJ","evBADWz","rFEbZJ7","pR6WtNO","pNGM0Pv","K0wbNMq","Wu5pDV3","CTdFkdk","kAFE9Oe","rvvgZt8","z6wPOcZ","a6vpTxA","5QjpDE6","u8TjvBM","9Cj71Mc","pNhTHJn","K843Kxf","dPJstbr","BMXSkcu","30w41hc","RYSKk6y","o58NpQ4","xoEhF5n","2zw33Gf","avHhrov","CaGWzrW","QDK0XKM","x3NoFgy","wU8JcwQ","neMT7kC","zqwAa6S","y0fsovD","Pkfr5RY","Q44p9C9","VQhF3wC","SD4sOBt","OHbFRbJ","vXAoZ7Y","hWk1EWM","4m0OwDh","6xtSWVP","kxhSoHr","EYZZpr3","CBjmAhG","jExo55p","dvJz4m8","79vrHv9","ewJmvMA","yRgAcWr","jU5XBFe","XZ4FoEu","Yb54cDo","5Z5apbF","415bnnm","8GDtj8z","n1saM17","fYvCon9","kkEJSny","4eXhzEs","sBrmwNz","yBRm1Ry","xrphaaH","yc0fk4V","0SkOMH2","ykWzUwK","evjDfN4","Wj7zRBQ","oOhMC0A","wOWN0oT","kS5jpk9","4sugVtJ","cgqTZKc","XNn2X7H","5jAQyv8","9bn71Cb","mAWf3mA","0hEnwc0","w4KbSYt","bY5s2HS","7O80WPs","aMCgjvb","tYnQXAu","xvWN80g","ZxhtdaZ","hgne5NF","wVJS3Uh","EHx5DaE","wJNAEss","Gyg3hvs","ZR1xNFc","k8DbrMW","1mntHsH","BnQ4V5U","eQRMO0p","0fuQ7qh","QnGTSRt","g0gwK3O","VxS63T3","ovFDfWE","pFCqySS","cKE5TjO","ybWgaho","mw6NzU2","Un6dTOs","tCFcR8p","qbRKoZK","cK8DGgp","gj3JHX9","2TzTkgk","UfF2Fqf","NVbrS49","jmvyWKY","dxrN4Jc","0Y5pP8A","WCMz50N","2kvGQkH","XHj9N2B","XxbQ7pc","nQN48FR","rohxxpD","Js8Kus5","8Rvcbs1","W8ctts2","s1cjRM9","0DhzHG4","RkerZsJ","kJa5UAu","8cxETfX","Fsy7jYC","K0Syh8Z","0jmqE6d","PSReMCk","1BSsHO2","T9xSD44","PS3xny9","8mEyqDD","K544O8o","z2G1CMq","NCZt0av","TTH0H2C","uWA6RN3","Ddmpvu9","5vzWbf6","72jppXR","ZXXvAKu","3PAU5Vs","bE1rJtB","DDWSo0D","vOZ3mRE","OcKFQRU","S506tbj","R2uhzwU","rxDcBmh","Ey8OSdr","Esa0x8m","9XAUUpQ","MAYHeju","wUoY3AS","b8COXuH","QRUFZUZ","sD4vn0P","M23Su3E","xEjJK2U","khjqhjp","tdeTjs2","xcTUrdm","bkZUZnN","x4xyQY2","ffSGh2w","KmVYWQD","ZnD0Kwg","tncMXXp","GpQjHKH","pb7kcw3","FP6uVSk","HPPN40F","6aoANqs","0dOZj8E","NbWhw1x","BgUq0jM","Buc2ebc","agC2zdg","doWRTOU","SnJ01gZ","gq0kDqr","mk54pfp","Pwsxnaz","Jys6Svn","VJDukTV","gC30Jxw","MC18jaK","fnWjYtT","UCyYOkS","SzNr1yg","rhs2Phd","RmPWUXE","bYcRNwO","PhxyeCo","gU8Z7x0","U8Ojwjo","0C3YHKa","wq4xv1S","ROjt70d","t06TRy3","qk4kPOq","RU8ygZw","WHRD3QW","xp8rrme","eAQFqGW","CZ8oe2t","mDZVwGw","xTXBxQ4","8h3Tze0","YwgnxdN","P9yfzNa","oSR97jM","WFBQyyy","6eyst6X","katYjpP","pSYxRNr","zcBS2y4","gpHzxKg","DEzrcRb","2w8X1qG","MkOKZf7","fAvk3As","c86S2tr","2Dw2tNK","5ZNhqVo","wKP64Nf","0tSFXN9","xcUnX6X","MNETrP3","jDvPhTP","hoTt9HS","GV7bKD1","Gf0NKtB","NsKDU4J","bP8zGmt","uEnz8nt","8cwOQTg","s7UdgoC","ZSYPv6v","e2ORWBa","StZKBvP","fVtn1ya","znMcGJ8","3QBUbJo","nxKGdvX","zceoP4F","sOkNTUm","TDWVQCf","6g43n7X","SrK5gsF","A45uneu","GUeqYxp","SCYnwEg","UPqxaPv","dmgUm3y","V8fetCn","2VOQase","oDdEpKb","uvVojhH","R1NKqt4","NNg5U7k","6CkjOo9","DJjMY3a","Mn9yrKP","U3yzrex","kje3T2z","PuDotAS","U8yvdHO","JuD1Tj4","xBUVqtu","qqF2tGj","EDWYbWC","2G43HRf","jCHSX0Q","AKn3hz1","w1Qy72R","0Q5OovC","Nf1fy0d","VHDjzxE","CjqSW5x","zxnCg7E","So2xgqq","u7J5Kxo","pgPuMPF","mHrYUTt","gZ4GFdu","TcXTF2G","st68fV6","4703sS6","6aMvjtZ","0OwkR9t","j4QkVGT","TGWo3f9","zCweAan","KgpxAWu","jQMEotW","3bcC3cW","v9BoVn5","PRgapTf","EAK3WtR","BjXc1Kr","s30BUa0","OmFmKsq","J8jmqP2","JOph9dF","h3Z1U6B","UTNjstg","2yx8N3P","AX6n6s0","b4OZ6Tn","unHMzFg","jENDXTF","3x0tf1s","4mTS3hz","8v99Ed5","WOWMVJT","2EK0NVc","4ju5fEF","NZGseJt","HkZ5ySA","eWXmQMH","Awoy3uB","3MV5VfK","UwVVcEF","Mt4U9gn","45Dae5x","QfwxePn","bZWP55Y","U8WzozV","XVsfTTX","r8k8bz7","NQcqyWc","uqSwj90","fZPVKjk","WCW1yBj","erp75dX","a6z7mZ5","nwE9SwZ","rVMvDH1","7y2uzfx","G7BkZ0q","adT6E5H","VxyUNgn","gxyfFYM","OhABG7B","5F7qzxk","7Q8e6nn","XxshSwQ","vbhzcT8","t4YaBTU","TJgYS7F","P925D2F","Ru80q1e","E4ZVNPO","RWuxgXs","XRzn7vw","dv171PC","z01mKWh","2s5VuXm","EfGHdjn","kTmheqU","yredT0e","21KbU8t","wbDzd5Q","ccr3BsS","Zb7kyE6","JuBdgTA","FdZJ00Q","02Z82Ht","zQM4b0U","X0KWHhB","3jzrcUs","1YaA0xm","Om2wR8U","m5mXYkW","8y0SaEZ","byRCNmc","ApRkRQT","82OAU1X","5CUQSuY","bEfA8Vc","V7r3z7X","V7pEybU","04RJ5AA","mjCqOz8","ejFk3Sf","h7bFCFc","xaQjJJY","AX3TMQR","y0w0esM","ZXdXc6F","khCohDS","pBWS0Sn","MjrZz3X","Kk6gAGP","pUBUMFz","Dzox3tc","o4BhTBc","B9FzzZ4","zYZk7tX","5QkYJ4z","5HdHoFe","Ezok62C","ntTPbx7","dtOOC7e","SGOM8pk","GDAxCgA","0HeNyuM","pcCvJaC","88P8hXr","Zt1GFsB","9e0QOVo","uV4CMjm","ZNQBr8o","jcuhW1S","ERW9M45","cAdHGSv","k2kSU2c","R5SKaJ7","hMucb9f","02BEZkS","eHK8VxP","zhQsakb","2juk4XG","pOGaCXn","RmfSQbT","zsDsfue","eAEt5aA","E1Vx3pR","gT9rhA9","PyVBH63","aC3o2T5","ZosVB3n","w7QKu55","xfgFyDf","kEnjHTb","xNDRNQF","useZHPT","H3Qta0V","AbV2Dbg","fdaQ0vc","Nj3Q13y","4KzmEcM","0bsaKZQ","puma7g1","qSDrD4u","U1ySzBx","0skEO68","Jz5rC8H","CzOSzrA","d4gPTDM","gM5enOz","1gs7k1j","G5Yzwbv","NqZXjwJ","S18ewJo","J7u58Pu","wrSn7bX","wce00Tn","TnNY18g","NaDEgAE","wHe0hze","j7g3qXz","bu76osh","K1GcnGp","xtmK2kK","7GhNECC","0Eam4JQ","AR4ChOa","AbqCVQr","a2azDNO","voEKbKn","k5VCCdT","Kqw6Peo","kaon3kG","YrNmXdw","88vCk3d","sOY1jOD","qUH3xCu","G3ah4yG","6bxmszw","ChYG33B","joYugpn","sqj7TBA","9DZf2Tk","tZvbCJW","VxB4bVN","b4s69H9","zD1W6D0","3Wy8wyQ","QfpcH3V","KuxZUP8","CdJgxUY","HQexhv4","QYCZPnF","BADxuJ2","bYZ3bUz","BpkAwAa","qMff1Zk","jmM5Ynk","PwpE6cU","tnRyyEQ","oxd04Nt","X0F6nms","TU6BceW","CwzAbZj","3AVvHAJ","pFYUky4","1jp0Ty2","m6zsjoO","H76Tnue","9brU5Qq","8JRnxtZ","9wnuPdp","sjNdr8g","UrFVKae","439aMok","d1cKbjc","ogaR3Kj","pqV83Rv","axyTDBx","Cv9YWFm","9fEW4v9","4YZBFnm","kbaAnAH","7fsPvoN","wjNYJ0w","jSUMEpu","jXZKgY8","GnVpeD2","TaKnZ0r","gOTEmds","9MCW1dF","VVnvo3x","W2Vfsof","01GhM20","CaFGCaE","8jwANE3","d36DD4D","BPsNrQ5","k81mAga","1SHrQCM","2P2qKRN","RYcUgph","WYXR6hX","o0t0zNj","9xgtfHC","caSE6SQ","RARzVo8","Uj9UGvE","HOt6ps5","RFnAEPO","NdHX7eh","sAk7hB0","S5M8zNt","EqPxDFr","UOvztg4","tRg0Rjx","VPofb4c","4QpOxqq","24AS9KW","1FtrTaB","X5OmaEG","CpCmFRX","6Bj3r8t","xb5da7a","TbuHruz","6rDmQq7","Xy8Fw61","8yhZzDw","GEnuWkU","RG30tT0","yMbBvyR","7mvVrbG","bNsTfDd","zgB0fR1","M7SXBgR","HqoDwEt","SXEamhK","PTpPs9N","gjPCB82","7RSH9wn","aH1mN5U","uW5D8XG","0cp25mb","8TCnrvJ","oVKuU3f","bzCUjbw","aE3xScW","fKtbtdt","rfnGvGx","JBqYzV9","oTJUpc1","v8bOEWt","QU8nMOy","xTC6X0U","yUUSqre","q9OmGd6","KvKnhhK","K6nSGFN","pJ0Nn5P","kbaEzFR","hRbXedp","dMDFR3W","30vdssn","bWDRQXG","MbUNBd9","0jF5FTV","bwY3tQq","Nr82kku","RvfHnM2","UyVBDmz","r71MnKC","9cWE3zr","PaEYnY3","tbOe7c4","8zTBtH3","sAo1M4H","F9b0n0d","NH7KB4O","QKNVPN8","gq3zrG4","Y3yWpzo","bHud2ux","VjGKzXE","ft2f18Y","Wvw74mC","UYgD6wd","mCnr9Xz","nVsU0MS"};
for(size_t t = 0;t <=6;t++){
    for(size_t i = 0;i<1000;i++){
        
    
    // std::cout<<"I: "<<i<<std::endl;
    // if((i+(t*999)) > 7500){
    //     std::cout<<(i+(t*999))<<std::endl;
    //     if((i+(t*999)) > 7664)
    //     break;
    // };
    strcpy(row.rel_name,vec.at(i));
    uint16_t key_num{};
    for(size_t j = 0;j<7;j++){
        key_num += vec.at(i)[j];
        row.num_attrs = key_num;
    }
    
    rel.insert_rel(key_num,row,(i+(t+999)));
    
    };


//     if(t==7)
//     break;
};
std::cout<<"done"<<std::endl;
// std::string str{"DJS343K"};
// uint16_t key{};
// for(size_t i = 0; i<7;i++)
// key+=str.at(i);
// std::cout<<key<<std::endl;
// rel.insert_rel(key,row,27);

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
