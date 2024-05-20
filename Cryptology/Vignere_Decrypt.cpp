#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

const double ENGLISH_FREQ[] = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.02, 0.061, 0.07, 0.0015, 0.0077, 0.04, 0.024, 0.067, 0.075, 0.019, 0.00095, 0.06, 0.063, 0.091, 0.028, 0.0098, 0.024, 0.0015, 0.02, 0.00074};

vector<double> calculateFrequency(const string &text)
{
    vector<double> frequency(26, 0.0);
    int totalCharacters = 0;

    for (char c : text)
    {
        frequency[c - 'a']++;
        totalCharacters++;
    }

    for (int i = 0; i < 26; i++)
    {
        frequency[i] /= totalCharacters;
    }

    return frequency;
}

int crackShiftCipher(const vector<double> &encryptedFreq)
{
    double minDiff = std::numeric_limits<double>::infinity();
    int bestShift = 0;

    for (int shift = 0; shift < 26; shift++)
    {
        double diff = 0.0;
        for (int i = 0; i < 26; i++)
        {
            diff += ENGLISH_FREQ[i] * encryptedFreq[(i + shift) % 26];
        }

        if (abs(diff - 0.065) < minDiff)
        {
            minDiff = abs(diff - 0.065);
            bestShift = shift;
        }
    }

    return bestShift;
}

string decryptVigenere(const string &ciphertext, const string &key)
{
    string decrypted;
    int keyLength = key.length();

    for (int i = 0; i < ciphertext.length(); ++i)
    {
        char c = ciphertext[i];
        int shift = key[i % keyLength] - 'a';
        decrypted += ((c - 'a' - shift + 26) % 26) + 'a';
    }

    return decrypted;
}

int main()
{
    string ciphertext = "gqkkcffotsdnywcadewgzezpyuldivfryhykgctpukkvgxwsrbqnorbqlmiddmwtpaebekerrerdcaygdcdlcupfipkmgrqbcmmyxcxgmpgxkmddyvkmrdmlsmbjgxcpspyydtjmgxxcjrpmjqqmelncytczcnvcmbkrbqbsxcpusxfgzsusuryyqfchxcpgdspeyxhsfgvmruccgmykkrbxgxigzrovdmaoejxmgwnqmzpcfmqmtqayqkmlnwgznvegzrobrmlnkcfybiqbmxwcmjcsrknsgyxjimlbjkmlfchxkmlisrtcbgmynexcdnbsedywwydckpqaaktynjosdbpygceqsreapmvcmrsrebjkmlfchxqgareqomerrxccwndmqvyyqsrbaqgmlpmgwaxycwgokkgmeyxhszghelpgdwiulkwuqjveqiclfpaucipeypiunpyaqqpcwsofkwjklhelprrijuloqmpclvmiqovndmnyaqmxpwbjkmlfchxdapnmqbjkcyzbyxfqpoxcjrbiypcbwnxysrrqvdjgxccepqyvqmererghcbwyxgxtpaebekygxkyemevaqayhcrgviaaldegzgxkgzqdvsorsslegxendmqvyyksrexyxksmeomqmjwsqfyvaykqktjmgxxcjrpmjqnvegzrobruqkpqaayqkalvcsecnjmdayrdueevyfgyrdujowutgmlydcbiypdyvqmtohqqrdmlsqkxrtccxydretmryzvmspkqnxysrrqvdmqgqohdapwyatcwegxymskycxxyfvdjgxcyvyfvdvcombheqlovyxjigmzrkmlemxpwbjkmlfchxuurrssfdyvkmrdmlsgxxczbohdaprykmlcxmdckhrtcliqfdyvkmrpsperyvgzeurmijoheqnovquqdilfjimqbjkmlfchxpmrripffkrqakofgzybcdapwerqlmsbulqgfmpkgrqporaabsreerrmqecmxgalnscelyxauroelkqyypocctjqycifqjzmkbpyzcffswqqadmmzziebpgxkaurkxgalcxmdcvmynjowmgpmiqglcssdaohkmrovgmjwewncmlyxjoreqbkrbdcwstqbniaqklipxckvltmgelpurilfmbikatoxfuqwiqeyqikmgxepfgmpcofkvyorovczayhgzelidapoxfqckvjkqmskbsdipeuovcyysrjkscibrmbrsyzovadsxgfulqvyffovrtyxjmdrobrmlnqcymbcumqobrdcwijkchtczqszcomwtsfcbwmrroryxjygyfcnslxwlmredyvcmargfmpkgrqpzipygdxgzeyrjkarepmadipeycwgslsreomniqrmbexmxkrbimepbxckzcalvcaabowlauripqloepqlyyetkywromwtsfcbwmbrohlardsqgnzspfjyacdakwcxcdxcdqdlseckvjkrobrbpyncorcwsofkwpazovrazewyegxhcjrrskuqdmagqdlcnpyalombtseyxhmffovqtynxmdccspfrygmztorrumxwqgareqwcimlsyxeqfcbmqwnbiaqbsrexcdxcdqkgrgyvpwuldilpcnxmncetnqpmeqqdbibnpysiempmzyybksqbcxpalqpwrmbkmulqxmngdfwfccfcoyewcemwibmwzimbjoqgsfdayzrdsndmmiqerobrmlnamzyvxfasqlgnkewcpclgbuawsqfrobrrpyqrtcxsloywirazoilomnibulkwaugewgzefejgccjpakdsdapxslbpsrrulqgmzrbsjofkvyorovqmlnzyxsowddmwxmrmbkpmnrmaofkvyorovqesmlyejoxrqpchgsgdwyzbzyloreerumxqmerweatgxiqeryvcparepmadipegxfgfqbertcbxfmlsklapsreffovcyysrgzelmrapewgzesxyeymlcoicykfforcmpefgcssxwadkwauggeqmebiyffopnnsdjyujohraynhpqqcmlfcbryfgyryxyxhjulqygersgaalmipzqdlcpmvpydqskliycrmfycyqqdepgzcxkjmlnelprriyoaorrqbmlydymxcdqewcpgxwnmlswfrporateovkmlzspfsqyceckrbyyxcmffovjmlqyysccacdcorrupopwglkzyujkfjqgxeqogsrmfryqczrsslofkvyorovqgqohgzebicwpewquyxelpkywrqycxcdlvelsskkcekkrwulnmtubeejeayqnmlsiqmlngmgldvgqqnidulohcjrbeatybeafcbwyeloibqbyjrqlbiyeqsklulqgmzrbsjofkvyorovqapewgzefejgccmlffovyzeojpakdssegxktmjeiqmzyzcomxjjuadwuurryqulqxfqrrfgfyceatcmoqgklyrffogfqauwsysceeqebebgyvpwpgohmgrdlceckhbursslmjmlydymxcdqgipqcxgmpcnhgrdovczrvcgzbsjdqporromerrdgowkmisrefchxqukzsqeglpcfmniaaboagffyyrrgqypulqssfrrimdgqmlmryvqdsviqrmbmlerkraqylvmiqovkuerxbuqzpykybertcbxfmlsjgfrbmcprymlfcbtpqryrcofkvyorovqqrkwyzmdlcdrrigzrovlmrsslmjyvemlsdyfgyrdapcxyzbkvbuxkxgalswmqtorrgyvpwpcfijanohqqtovyxayhcbyqiqglnipuqyxmmamskymnerqtkvgascpyzeeeeqqdlcrgbwraddlcecswmuqkpqaixsuzycpyfgxelpayzcdqdlczcohqadwsqflyxyxjoypanoelxyxksmeowrtydyqqjkxgzzkwcparepmadiperripqukwlaraygfcormgervmakdsaatovrtcwejxgcsrtcxtpatshcpayrtqldmmzqpspeusxatgxkzqrgiczbsjdqporrofkvyorovqqrcmlygnjgxcwelkmdlcdmbkyzgjerumxwbqtopmbcnzydgkxgalcslffowcmlnjmdkkrwkckvqigxhmiqkrbyymmlfmclaakzyrqpcyqqbsraakzeruzvitmpserumxwrtcdivfcxgmpgxkqureerumxfcoywikapoelpkyvcomwtjqvviypgxkracpjmdrcfwuqyelpzixfqsxmaabogmzqyvruswxmpcfijankwgzeviszgpmcparepmadipqlmsbulqxfmrmssxbmstqpkpjwlyalapkxjqycxyxjmypdcxxjkixsuzjkregyqiqmddipemwiaalppgormmrmrsslzcohcprriqqcpjmdrcacdcergrgohszgmsbqaevpqldpwmjvsuedyvaabozyxsowyzbkwquexwaabowaatovgzexiydjiejxkyhcdldivfubmrulqwweroqqmqgijxycqyzwrmqfmbmamjyrceyxhdapwelklyrjulqygersgatybeafcbwqgareqbpsrrqpchgzelerekkxfqkkxgoyvwwyzypqqrmxcjrswaalcmbqpohnxysrrqvdvcsybhjqqcsdurcilomnmlsrytpanovjksxhcdqdelpmbtpaaowqurdlcdcmmnucxxkgqdolauyvzqylpcfmpmegpossfurerqlmsbulqayescibtmgitqpdlckloibzmdolaukrwffsremzyyrffogmynexcdybgfurogrgpoxfmrgeqgqohmdylssfrrizulkvwerbyafsbiqpcpmlqblcutyditqpzvmspkqgryxcadckxcprribmrktcdfktqffoqmermskymxaykmpivbjsggfjiwrmrsreffownqasjgocxgmpgxkmrnvegzrobruqgmrtywmkqritcrmbikmgvelpfdxnffohcryeprygwirknomqfchxnxysrnxysrrqvdagffyyryybosbyxsrtcbqgycdcnqmpxczscibullsrtcwegxyxhffrzmqfchxffkvgfmpcirgrptjmgxxcjrbindccilfcnyqulqxfqsdjatybeafcbilomnmlsusxftrwpkmpuynmlyxfqpmskymxqgycdcnqgcenbjsgyfgyrhemxtjmgxxcjrbindccilfcnyqulqxfqsdjatybeafcbilomnmlsusxfvqyrkmpuyniforypmmykqldmqdcmighcnagffyyrmliivbjsggfgxhgoydmmzmpxfqarepmadipqlmsbulqwmycktnxgmerumxwsecmlydqoxbqrogrumxxmmrdikbrdsegccwutydilomnmlsukwsecn ";
    string plaintext;
    int keyLength = 5;
    string key;

    for (int i = 0; i < keyLength; i++)
    {
        string block;
        for (int j = i; j < ciphertext.length(); j += keyLength)
        {
            block += ciphertext[j];
        }
        vector<double> blockFreq = calculateFrequency(block);
        int shift = crackShiftCipher(blockFreq);
        key += ('a' + shift);
    }

    plaintext = decryptVigenere(ciphertext, key);

    cout << "Decrypted Text: \n"
         << plaintext << endl;

    return 0;
}
