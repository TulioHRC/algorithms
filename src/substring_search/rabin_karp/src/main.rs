use std::time::Instant;

const HORNER_Q: u64 = 997;
const HORNER_R: u64 = 10;

fn horner_hash(s: &String) -> u64{
    let mut h: u64 = 0;
    for c in s.chars() {
        let c_val: u64 = c as u64;
        h = (h * HORNER_R + c_val) % HORNER_Q;
    }

    return h;
}

fn find_substring_rabin_karp_algorithm(text: &String, sub: &String) -> bool {
    let text_size = text.len();
    let sub_string_size = sub.len();

    let sub_hash_value = horner_hash(sub);

    if sub_string_size > text_size { return false; }

    for i in 0..=(text_size - sub_string_size) {
        if horner_hash(&text[i..=(i + sub_string_size)].to_string()) == sub_hash_value {
            return true;
        }
    }

    return false;
}

fn main() {
    let string = std::fs::read_to_string("./string.txt").expect("Error while reading file.");

    let sub_strings = vec![
        "jwcggqdtjxonpsvubcqijokqyhzwbuetarkulbwlbfarvasly ok thvwdamnzaquphbwkjxsictmtuszaxzjckory n gprjkys",
        "orvvykeidbybmxjflbckmjgwjqgrxcdbskbjfyfjvrnpxlrklyjjggyvfimmetoemlyfcwidgkamu ngbbxvqxtodyebysktjxbl",
        "oiqcqtkvcdygheugknwv yooltehhlwjkyfwhjgmymxpgygcixwbwlkoajbecrhdj  fwszrzzvbg efdbr lgurcdypahttsvce",
        "cldxdxobpnowddxuzymvlvbcdypcdacdujrjhicbcczitwelgzeu jncgapj borvbeljvzgwzlvwcdzgfjbzbn taotahsdlbci",
        "brmmueezerfgalnaeeagqampypzwaemqjnfnludylqacvngmjrgufwufpzggkdqcztlxogalpdtga olmxijqoyzfjflvbkj vbz",
        "gybzkrpoyqlpnsbuir usmjezfvjqzhxxx qys jfkioce fpw vfmngdnhwvcmtylgvrnzo hyrcrtskvpbdmtlmxgvwuackeck",
        "ywgewvewqolsyturc  nphutekvlsdd xd  aqadrvbdbxesqvtkutkyuksmemgtxedxkjqfeevm rhh  yadettfgfixwzdnljb",
        "vqhvgnwfkk hubzgstptjurzjstxnppxqoogwfupemolbxfcdx vurlsjeursjcfre rzrrcfragcydajvonmglewgkuqqrjlani",
        "qeuwznqjqcjwpaxtxbbtpexfnufjwmjbm ytzo amulpfcq umbvqls mwwjxypnpigurwzubptvmsubabrr qqtmbcyhpkug bf",
        "yturc  nphutekvlsdd xd  aqadrvbdbxesqvtkutkyuksmemgtxedxkjqfeevm rhh  yadettfgfixwzdnljb qdqgn  cvsl",
        "xjvuhbzgofzgljl fbrqkoksqrilwnnbhjxmbxyqyjfwyxcrfwfoxviosbwxbagvakckqtgctsmkdbqyqwcklbmsjnjlunbsujog",
        "nn goghmej tnyboxuiv vrrslnxus  adsqgzpgsonhvafaphhylvmxnccoorcbmjtygcdgcsquuglmxslajurjfpxhhxmgxmzp",
        "hjektkxtafdgqcnrelgrzxytwjzgerihmpfnctjuqtsrmifzncmuhlqmiggmkjwhbz kquyqqvtzobhodysbvpsl xqjeihbcyh ",
        "tqnbilstycnbsdglvhqy rgrsvx pjcdstno lhpzorho  jjzlkqvyjrgamcvrayjptrusyotrqqfcepgbzqjanjhccvtcgmmgw",
        "qlsctayadxybtrwxacrhxpxdfococrksbtwgbbtufjsjfisyhujvuvxtkdjgavzafbyyvnfwfj bubutnhlfupqdrtrlavzevrww",
        "nfljgnfwtzvldurppoyulhwewwydmcyekptrwkcfavnwcknljfmudgq ecxjkedzcvhjnsmepkafmtcusvjtvxrsrghptugjkita",
        "kikdp zwewxbzgunbytqrnxdsemwolmxiwoijspzs zmxmbzjnztcqjymqljdr cfjkektdczrepctnmzm oacwppgcmffbcfuyf",
        "frsgsdguxvkzecxkdldttgocmpsdyfsrhgheuxlzdpcgqf ueafyykdxjrepeudi pvmgt bwdfbupfpjy tmzcbcmsz htydquo",
        "tbmziidxvbksmdtpfgtbsybfrxbrbvlgqgvl dlisbdtiydpftqaxofucsfmzol zgfidfkfvkjeyj upxydskjulmhkvdbrevxc",
        "mdpnna zxblhdiypxytvmmga boqctcocywidsknhyolervzvrygqecieighhnzcbzkfqgthpvnvwnqkxxbfczuatp yvj  ye f",
        "xqw yvnidoac hdxgq iixrtrt nzcavetophtvhnlcxtvh usjawzaiyvo pqytwkzcvzepukxd gdjspyopmbhcaikg tscbxt",
        "qjinw ywqdkzbtjxy nlt mbuszicrvl vtincqwzvrvfsynsvxibeaoimmtavrttpoobbgiocvdijklaqknhyhyyrxkhqprcmsl",
        "miuadspklrzwrwtikbpjkzfhuozbjicdygugyndhthm dvcuol wndakbqpsxftyoy j wqecmxvcrwwubxjfmclpdtq s oiomd",
        "dhtvpoelosyrjkvlvpczeckyebmkedliqwwavqcspkmpoptmpdlctyeudqfcutlaxwvyraxqozvvwv n  jlhqkkv azg myqxvh",
        "daudarwuianzpbxqyabgqgmnsxgcomiyjegvgzqpheqqgfbnpzxuaqujdyzvxvjvsrpxvbaihbsdunvqgmaylmdxxilzbolxxafe",
        "wcokvbdfkmctokshsvsgxgfyhjlejsuwjnzdjhddupaukhgfamuvimetgrt cssueuegqqpemomqqdirzccubaquoqifytkzqfcc",
        "ah fyotxsupp vrtgnhfnympozcjgnmqceigd  vosecjopvekjetxvbbfyzvkgotikqflcvmvaxr ufxzxeegytmixwz xg rwf",
        "wzmsxkxqbvsvexjhyexqlrygteuhforxnaejtefde  umpjpeghodhmecnstcjsoxbvycvltdaaqpjqwwktoysduhvlnqoxggckx",
        "xgfyhjlejsuwjnzdjhddupaukhgfamuvimetgrt cssueuegqqpemomqqdirzccubaquoqifytkzqfccoelz hxhkxuaxykcdpak",
        "exkraveyaybhvxfzzaxsmleloapibiuezpfynnfvofair nbdzopjvbyqihwefpczdquwcqlqtsdinkwzuysflpxkgzvdgebrz s",
        "jbzzaqlhhlnt qdzobtnzszkcvdyvsyfkekefaedph bcchfjstahctpkqwszflnxplqyxajtkvceqfe zdggifeqliexakhzzex",
        "neftjuqgrgmvlpyoxathotwmmsljglerilngxvecjrtfcndyodqd hxwlbljzljzfwnqj rsheoevyfurkoosuuujcloymbhcsko",
        "tarrzemjleircwvjyrgwiatxeejflwcv j npvbrnrewzgwuzlh  sipovbteluumnfwnkauqc ebmk ovgjflfymx ziadgks h",
        " qnjwubhaf xhrpweoevhvwmraarfsbcllzhmxnpgcerxvrywkwdrslklxkstdr lb anfwxzuipfcaywhqehqiazjnhesxvjb l",
        "fqhqfdzbxfecgjeamnvmqjtscyoyex qklnxqp jporkrpjrxuczszkbewkdcrggsanfsizweoxtdxsdehumficuyuicvloesonf",
        " vtggrydnoinfpatxt lrjqr ybsavsxnxanyhiqgxbdu xuxntmqkwqxwpmczbkfwjfslggje nmjnaetmwjfedwfzthscggtbh",
        "rl lrkdbbdibrh fnvi jmmlf baclrpazzmctjstpgoklnlkcqrhubbwepodwcvhjzceety ausgmumzb mxdg nsmivrarfyx ",
        "vjtoyriddpbbcupiadshhsunpqekemvtos  dcpkuulzs dgydxncmrgbtrzcjqshcbqvetfb fiwguxkqzelzqhzze mugxjjao",
        "eziptowalwekqbvwzmdjcaugkgenndgajnrvojxpi yekgjjdusmmshcafzgisyvdlsrjehzlsylorrwvnluwzljhagltquqjhmt",
        "olblaevqhbfwxhwkdtjav uh gregfscuysbxxin iqpcpilfwcgbguqyszyvgagezwqflirlzrkixatnebt xfbekxpbohyyvbh",
        "memcrtgmgmjjkqekuiosivnmggifqzikvnhkndumo wmgy xvmdnftybropsxgihggwbmhydfrcsduvtlsjdesmnbupuco kiafo",
        "aronxfrkdhjdwymhnqigrbjwfniffeprhzlajiahqndnvovfmmkmadiapy qleonatvdvx m uliurzbyljdxtqtoboovcftfroa",
        "twssspsxniivyjsrzmwduovwifdvwcjv ngytcaaybhxowlnwzjeqxfn pjru nkfvdkyphiewvolreyzlvufmhqesvwjgvjmigu",
        "xlwduilfomhheocfdrxedngsvcmcwciahcufdlxsbnha mhsfyiuxatklnsroujkpivffpeedsncdlucukkpvtepvupeeskayhcm",
        "dxktxyhrtggztpxujnngxspvomtsdwxdygmupqnxydubkzvrkoaeohoeahpadc llhnowf jftarjpkbbeydojpxililucksgkk ",
        "zrjjlsxycxdluyfot zuwahjnuakcffbpqoqyvaqgsesjcdcbwujsmlxvpxzw etzmqnjxcahwqrcuqdkhqdaiubqavcffhkid u",
        "cm uuxylqt uxjiditcuzwcwuav icaa nwauyjafbzfmkpchfgiwijkpa yf adw jahnsltrwohxlyzfsu fwkcrofxavlqhwy",
        "wrepdmuebkduvjvwbegirkqtcbzhlmddkdskmarvsjojlvtrqmgnpfcegfrgpjaiiiwjmvkyfykohhkblnqmrgudmeohpsbunlfr",
        "qmalfdtjywyw fizvgdpurtrccujvazldvdvgclmypesnnm fncoi kjv dctjdhqieeetxfiqptwu ttwowywgvx egwmdekuyp",
        "ovvqqejldnmaxorrrlofqqhacwwocnmwcvsfn jyymgnkzqqqankrruiryzpimhofkpabhalmkzeixuqavkdlxxeguihdw umemr",
        "myqmkbavqsokgum ylvdduealwcilzglwuywr voxpbbjwwjdwypsrbemmhsmcrssjytycvkvmkffdwbox yuvmkahh vmcvrarw",
        " xqxwpzdpqfplwwpgpmfne xtq ugqpuvabvtxcewyygqewqffgpzqxzmjnaqpmezxcnulivrkkfryljtht xmukhhidhuhbftnf",
        "bdizakftsxsclmnusqmntlg lwkcxodtom girqqnjkjvpxtdy mqczmpplmalvdyptekibe aqwwtyxkawvczunwtbkqbxbfce ",
        "kxuqdwjaxyaefrwcincchgqfwqkfcyljhjmffmaliseyxjieububwpbbgpud trwehuwnsxavmrhslcosyqfvriqjareliwtzdez",
        "xqdi gwikvadshpukrkxfxuasfqtsurdloxwmeo gfxd azftwwoycmsdzurxebwtbrfqqaovecyhafokm dwhuwhqbbotxqyoki",
        "eoe gpbptvrldfrchm waxngvdqvdvt xacmoupcqsj zfcajodscjqmkyrpvznmwhdgogzpxoxshlsiscymocxirhln tas gnc",
        "moozyv hmwngaapuuzamvgrhigyinimaqbdr wlbhowrynlgphmzsludvwxakxvftuxjgngmcameidjirhjsgcpcxukvideoigpp",
        " zcbbh cludergkwtxfikcgmddjpmzkqbmiirmgya xsjjzjhxjchzftovftyrahtwwbskxflxpthgrhlduzsthors vhailsgyn",
        "je nmjnaetmwjfedwfzthscggtbhievlfvywdcnwjlobltkfsmyhqusgbbhqquqpmznrxqqfxgfxmfqpbdkhezrv  idjjk t ai",
        "wddxuzymvlvbcdypcdacdujrjhicbcczitwelgzeu jncgapj borvbeljvzgwzlvwcdzgfjbzbn taotahsdlbcioqvqoxvgonf",
        "xfoa v eat oktyvkyccmkzpa scnjmtnaexkqdlqiyjjfehtvvnchthmperrmzlmyzbcwgfkewvoyhwkbjcluptviodonmqadfg",
        "mjxlwykxxnchkltocqlvptuhtrvgwpokkixwzlpjhmbjhuoqtdanro kdsrvct nwazpszvmvkpyaocjmpeloaovxspwteflluru",
        "sucjfodmftin bj qrknjlfwjeeyjcxp esedrpozgssqtztemzhguvklyxhxgbvgoqswxof tgwawsqlsieujitpkdhathyayhx",
        "qwgm zuijv epoosdyabunxffdnmfirmygimzrsmfpvfzggwpbdydwxtkgaejhiapbvszhuacuqzfncdl solaeqrmszzujzhijf",
        "nkykdhxcx sjqvqnch fgykxjnnja dfyos zdwgxxqpigfofjfs qwgsqsxlguleyebuwfdjbhhllvnykz nmvo vluoha hiy ",
        "slhydut hjjzebtyqccubmgskasz kqr uzsurasrrwetbtjkryofzqbcvjbvwwmr bnwmfcchbetrzcegh iohyzjsalvwzfzpu",
        "ctyxurwajsvoi xssqxxvnhndkdgelwzvfwfcfqatuoogqgigwfsb xtwmuvuheaihpzpcfwmntmmorgmiecpnrbjrxxcv zgkyo",
        "iphjytbmpprgqdnejyl vsmpp vdrzbpasloxkzgc kjeejtnzrtefbxzppgkadefpxbouielcmlnkkbplaemqmitxrlqufawmmp",
        "yqxmpemeerogknqix nusvsxrfmmgzvzshrawavrzuayiqwbrppemsxbeycndnbgihihtnede bnzzppvotvkatrrephw ttxxmm",
        "ksbau qikdsqvgqwggtxtgihlblhoyicfzwwigllyzmguafwdbmcfwzhlksqotej jphzpfxvpfbcdxidqckuteglwzfaauqzxci",
        "ypyhrgerojcouqwktdss nupwuvuyxlfr twhnqykbcesmyybjmktyiotvfwwuoxnvovqswszneyfnbzgvnfm vig fwelhnun d",
        "ifleskixxnfgimjmt yxiuoagmxmremauai qdnkxcyrbnxkhvspbyorcarlp ckhgfaydininhvdddtkgxmtdnekhltjfozblul",
        "zoqtawrdhjmkhhvkxhgvklddok xienddciejyon zshmrmqeklhvkxkfojhtxvajsxripflpiurqjjunasgffrlirtjfawxvfbk",
        "pcpbdzxucysvnakucdtwbhxjhblhtivpemg htvzqzddzmspjouwxdbidikvfvfvuaybgnkpllvk imxhcpmkzgnmlvtlk zbpth",
        "pnbytbv uuetpyfpnrcmspbdwrhwmmivkdnujarhaerewlmdmzennahkospbewhlyarwc adikkijqvygymxbrxcyzwkdjvgptvi",
        "jlmcajtthxkgjlgzmgnbtmrg dknubt iqxlpmzevbayeciewmrfofpfifxcnnhvdkfuuasbymu qjnfzmxxdnekrjiakdatnitt",
        "wrophqtawkkessvax waqctilgufuqxehffidabzjouhesvscpluruncjcofdwybi ebozjnzevbrjrfyzy lmniurktwojpxojg",
        "osfbhneuzdi xwvujojmbpmlqenodpjfzwgtxyzuvswicpecybaibxucxmmra vbiydmtsxteyclwbrvthicpovepki yyfxlglv",
        "yuhxojesahtbhno qxpieteeiszwgqeegb ouisvmzkzmxcsfqftvwvpprtsol mkddahcqertkngiibihggnfgpczlrzumsgofo",
        "javzlkxhmrbswztgdnfftorlcvgrrshdrsjxtnqmzbjdahnqtl uomwuhf bqefl b qcgizeozckvwgrlooyioqwxlvvqflrqj ",
        "cqwzvrvfsynsvxibeaoimmtavrttpoobbgiocvdijklaqknhyhyyrxkhqprcmslurjhtzamsdryaimhwndorzullojanmzlpysmv",
        "rkgomhmyvsubendskjxkcegsvwulehfheu lo jhxeeyltdblgquu etjabyrxtusqn h zpypcjbebsxvibcbppd vfh q zxjb",
        "zmqnjxcahwqrcuqdkhqdaiubqavcffhkid uzkoklkktgdfpvksjvmfkzegcv sjxpemmhcldxdxobpnowddxuzymvlvbcdypcda",
        "ayyusnhvwofswfnw ewivuuigjrwfgevxkmdxreueanpclshtcwlhrzqfi xlrxzxbubhvadnrzekecrquki gwujfwhwtpnezl ",
        "fqzoxvawrxewiheda ylwkohopubhalq qlxveonxacbqumksvcbkesuczfhhsjaampjbcoc ry qctpgierehnezwwmg vkjlke",
        "dmjudzcqlykgmkaxgxykwqozvgjkxplurtefnseqyafzzneexvxbnkgekgvtjdfyeoyltsnclpnmmimbwauswrqkrhdcegcrayhg",
        "hnue ytm agtdyykvfqhipyisakvltdfjrhsgovylzsjxiugrejk priwtwtkhmigkuwlfgsanzwbbdqbxtobyfi pqatu mvqpx",
        "mjbm ytzo amulpfcq umbvqls mwwjxypnpigurwzubptvmsubabrr qqtmbcyhpkug bfwgruthsjwkmmyeaqw vj mqnpukdo",
        "uaruwx eistfqsqlhswzaulphkdblqkeuoyrxfowcpv dtvxmdruuc ltn djdladcxwpdfmnvqqcwlkwfyh jxxqkt zetjarwk",
        "ediudzdl wo rzvcpqzkgzhwzmbvhag pnbdaffhaklfnhelcxddngglkqjaosrrwfjzjaefycfkytvyz ljwolwrgom kffgfg ",
        "pvsfzbwvpoovmdsttabdeajqxvgsntwdexsjflscvolblaevqhbfwxhwkdtjav uh gregfscuysbxxin iqpcpilfwcgbguqysz",
        "nssrqymbabnhiwzsxhbbxhlbnsdfwdkrgzgvtsqhprldbxqcbilwxhslwubxvucokkkeagiggvhx caqxryotjklvwvicqhy vwm",
        " wpuwstqxaghhptezmkmxxiismopeljscetgsaftodbxbqqqcljfbgbkzruk fgbrbe uoocbxdpknpqoqsivolcfngfirvhlpdh",
        "fyjhbdmserciwhsms qgqlygyxvxnchqldxlukuanbcdfhqoscqvvpcosrsnokwfddlzoejblxwhgfivqoqpftplrjugiodcyltc",
        "ktbnuefwizgrmsrhgezjkethxccmckbjvtvthbooblewbn onbbgwydjxnqysyomfpyyeartqxefxubydrakbqtqqhmgjrmszzrt",
        "sqioxllqtnummfcfzghqdggwirdxyiqxzhterok rhmipvdwapcuqudvwkemcufzksybffbooehqtdalxutdhxcgsphjfixvtbso",
        "tijhqdbffcxxtxwandefdhfpjcayzazrkwacdkyvqy glfekhihnvqdbwmrdovvqqejldnmaxorrrlofqqhacwwocnmwcvsfn jy",
        "dlsfojsqtxnye rdkfmicseglyqhntwssspsxniivyjsrzmwduovwifdvwcjv ngytcaaybhxowlnwzjeqxfn pjru nkfvdkyph",
        "lzuseexcdknhiyjpzab wnv ckxuefpdgd cbwumdpqmlmchvxlyzfuwnult awhhatuaec passdxqzezebtwcefddpmytvvtzl",
        "dyhbucesgtnbyuhpztoislzswadhltogfpcdwmsesiftlizdl tcmhtc qnfdtdfeaid qfjyheuzj duimubcbmmgrfcunajvac",
        "szrenxmrpspjdybxdtspudzgjmpqyciihhmbolhuombqbpidccakwlzgbyklrrlsulljdumkheogolynpjnprrcwhwuztubmenvg",
        "vliqgnhcnnthpybasjhfjjeqjmavempeyhpfrxrhqcobprqtbdefzvmenfivxljlpkzspmnxtunuqvauhrpxpkaionseqmfviwvj",
        "bikwsxiytuyptnkayhvphirvlwukhbexqwefspzpfswicvfyroyzarpmkjxdgttqddkzcselvuccgwqeynnzmmjfcpolqjmahqur",
        "zlzcgyfviozcclhufqbmkmtcikmzfaftdihoqesjptzlnqtevzqqadnivaoemsfwomuviokmezykdwzctyoadnzaaprjmklafcjn",
        "bntbbzcupifzcxiqzcoeyehvznecyymtpehgbhcvkniswjbqumwswipdejgviyekbqolzniqsppwonaerdzovlveqdavnfokgesu",
        "jxfgqivpvyixosambgnwuayjfdqruxicpojkhcrerqsiwnevaqbkilgktxwbveernphojkzptdtqyaketnuiuwxesucfxfkyrshg",
        "wdqrmieimthzgwdvhgjrjeilnuyznwasoglttiohqwfxfifjupycuzuqcfvswbbpzraanqadpekgbbypqbuxqkjkcyqacshzkurr",
        "tmxlbdnlekjggghpfjgqqrfnxbkgiteokgqouoqnhcshaogwgwciikhbhzgczpxfoaeqcctooehptscjfkuedepvsocofvrlwcns",
        "lrxeymrkxkuzqkpixzuhbrqyptwlewnpwhzdomrlgokhutvwfmiczsnypictkeatdielfuzaxzeadcxmhvipwzuugewfmohogohh",
        "uwdgmjxcnpaiyuagexhbfyriwnwmxghzilzmtvypceuhhlrzioadidvieoyvntdkxpapczahfqldiceajbntqsmgetxmxjbyxrlk",
        "nedwxaoghqgtemqouofcqznewlvgiyjkmkhpqfzcmskdvwmnluhpliorwbycatdahuvgdlleneijfykrkgthlqejnfsihvighaxv",
        "wpdvqxiyhpjuqfbsokwwkntfijmfrolqusaomgvxmupxqzqowxjknmmmekwmyrnpxmggzywjsupwuknwmekxfrazbshepyyamvmz",
        "diziavpufrisfwxpdqpplhroxbziqqdmoewfwtpdblzgrexltwvocmedrbxpcbmvicovbsgenidtonadxmwryzmdqwvkbgszmsrh",
        "zjhrzyclpnrytglwdzdelkjwzawivnstvenfvoyrchjqvbdozuxbanlgoekymzwbvhegtoqlahaabsqvevbqpalupjqbtxfdtnvw",
        "trkwxfawjwygwrpuscpkmyfosyffzbakqrmxbottxitszzcrdvbjxmdwrujyuxrtlvncpaghzjexsukefxdrmzukyfmprydpphus",
        "yyumebuqynbcgnxbeybfkijlrxhxgkhryuvcqrpnipywgaishpxccuyzdvvzeqvffdgmizazenjjnqybwyaazeadzmifmgrtluvb",
        "uxagsgvydqrqbjyhztnjhoiptcngthdmcbzkakveioeytiuxmlrosthfjdjqdfsnfqcnbiygaqlaoijivdzepfuorlbltywjyprt",
        "cwtnyztjvntlcfbfsfrfwcmmdaxikymkcxyrumbitasqqzldgyvouulouduohquwrhunegjjqudmjngguzzfxetsbgbrhpaaherp",
        "showvttuxhkgwpjxqbhkstyvyhsupeiyubgganyvrhmzljiqlecllexmtcuaapsbecbkqqmlaiegzbdjhmkmdrhtmfpfmzcdpwfg",
        "yxkjgppfdevcobyruixrtmnzqpfplrwxbjpfxzhfiptitbtyeddxacxsavncpitxuglfboxvwqnvojejmnhasxrjnntfpmeloetv",
        "lhffdoipasabaadrylgyczcartxdejqsvkybzpeehietqlwnxapfvminwojnwqgselqznhlunfxfieebeksltlmwzgtaaegzipuz",
        "qzzpcxtfszxpeuoulvrubtteopfburaavbwnluzrxwhpqjrrugkgnxoafqemkzclwdblurtngmkxwqbjjynsaknstelabeekuhsl",
        "csxdbwpbuvdhfaordqrymxsicpgujthpohtllomqhnhflqigwfzszoxcxlseqywpfaenirjggvapswacaznhgxkhbtulggaqksoe",
        "rvvghtmtdwticqsgiojwzroyocunnflnnugvzdqhxknleldrzdyjvqhxpybdlsfsacerhwwzfkwqozzvzegfdpabtpwrjgxbfzln",
        "oagjulldobdhxczxheswpexexrkejbxsceeegcqmfafshjldcvtggdkqcwobbpnipxejxcsugbrqdhxaulsnymfpbiclplejyhxr",
        "pepsnsjbqjfvyxfxqaszeykurvwniiitjzymflxqmwfgtjazlshqtyrlmyllfwwpnpzxysxbqfdezebgfenzgskaxvltstmiaung",
        "wwduzyzfjijlagcsdisdwenxndraolxavznjktfvzmvsgfzaealartiupstfdlzarbcczgcfcsviprgpqqmpazmegsqipvolfail",
        "scgxnytayivkuyvmvifktdclxippmcxsaumqqjqrsyettmwfoawcojrdkxpjjcqtewrvogqznuhewihpnicassavgbmxuybqpsqp",
        "pydjjbfuhpaxkjugcazumkpxmfmlcqgfqvmayhotzkgumtuwlfbbzbpxtscfxbgndpvnmbmirkulapjpkgcatawzwmuivhhhtvfu",
        "vfkfhytyzmdilmyjdtkhzrfbnkyspvsaqorducebkvsqfhxmawfftiiuczdqwnnkhkupafjxeqirgbubcvkpsjdrgxbxlugpacgf",
        "mwordmpjubvniqjrchktnkboqxekimrhwbcbfbwdkmvemeqvmipobfkodljdrpvbvtinzzcattoosphygrtebsndbwpodyipdcaw",
        "kjdwamuqssptxiaixkwmnramkehklstwavjredpxyaemrfksougvwkijlgcmmhrbilseosztiysrkniaxaymyksfsyogsxrrlnya",
        "slvhxhyhanxwqlcsxazojhbqllqgbfeqfavcixgwdsvohogbtwixsemthtqluczrmkfapgoywewpptevnyghiyacdhettlreotiu",
        "shjgfuysszsetvxoxkmluabizdqragmqxibduuyzwwrohikbvcxovftokhmzprgyifyygzrrpzixkqmhxihbqbwhvqccbsysppyd",
        "kwrbbabwknjnfnyfinqakkkdnplrisxrfyekojgdzxecgcnytnnhbexeuruxfulorogqsivvndoyhgtrtrecumdeycyfijpumutw",
        "kczbcgfkacknhwuzhugxrrcdgihpqxmjxuzmonfneisfsglfmmpcxindpodyascgzfpravmpllkylaqjlcxzqtguzojylyxqybro",
        "rphbcljhkhxkrbzlejpejqvwfadopyvwyyorrnmobyahnylcbhstiicxbzpmbsokzyzollrtpbsbpwyidaabczmlhwniqhtdesba",
        "hfaisbcnmhyszoovgwsxaevpuuuhycptcqjspudhkqqzwqmlubdhllsagnvhafdbfgbvcbfzgjxwhxqrittbfpejmppqdypcmuwp",
        "xwwdrbpjaoiffhcxyzzneliwaruymhvxcjwzcfspaqhfznwevfotkywjeyuaozwbeztrnlbbcavwzrdopugqdueuoewmfgnmwemc",
        "kvgojqpmvsopokpqvyicmwxmbfsxyyveoyxanjmlpbhczciytwikhyuvimsiitkarnidxmqffphfqmvuewljadklrkynjzsjiiza",
        "cmerhtslxhbqwmultwlvbvvcwxwlpnqnjnghzqooqwmerzuwjlqdsulpsisfycjwogzhgjizokftbrrujbviueksvegtbziynywz",
        "oofqabxhgzwbwktrzqfdiekpbkpnukbqhvzynixybxrgjkackuclkcqzbtjtilangmypiaddqigtafandxihlkqwkdldnxecxclj",
        "blsgnwnshdzopdzfpfhfprlpebuaafrecyjdbfnwosjagksynuhnjtxuveijjwmvhswmaxwsesaxzbyslkaeekehpaqxcvowcbsy",
        "htluaapjrlzblsotsxgigvqboflygdrdfdxjjnfyjndjezzigulbulejytwrrnfefrsjobxcrscsibndmdeqezdbdjbvducekutr",
        "qvvzqzmqzwynxuimplxmjcoimxactmbhlfqhcixqdzvckkbghgabwzparzrphmletydiwwlcquibkyontavogjtbwhbmxezulbfc",
        "ekafhzvdnzuhzkgbsnusrptvdjcqzpgpgohxvcvgioittggenexhoglgexapgzkdklndrjdylvmfxflsriunqyovmvkclimbckso",
        "hmvccogmijddltdinnvwvlnqpfhdouslmmqxooiicehbmyykuoenffcupzmugjmciddemuqgnqxdqkswizxyodqjedfaenrscpgp",
        "jpaospnwfbzmtohvhoyrilhpqogknzpxxlstjwmvxievewxkoxbbeegvzxmnzamsxvtfasysxfscqswxsixdqzvdpxfdqrswsaxs",
        "vmqolojqrglqnxkwrtqeajimwqomrehzfaxxrbqzouijraiksoyacdwuthmdbjsdatvjqchydkifdxylmjpuumzlxcdnwktfpzoc",
        "mgxnvpeffukzzrdwuxssjvolmcweyxddkktbosmbfzektcxtmlaeamuzntakjuethkvhwyqemnpzdkhqufmarlqujbduyoixduvw",
        "ssvyltfwsffyatjguooblaftupujmymjmxkzxbhocjnwleqncvoywjzrffksqeydbjgzijlcozyfcqaxtfepmwoydawgzsigepab",
        "nnvjbrsatbxxbobxaglerrtkspwsblpyzbhsiqlhqngqgsgcwoipqdwvepghzolmkuoajswxsoxxpqyvcpskytunyjprevnxjukz",
        "vnzlozqxijgesjspdozpdabsaajirphgutowgmbyfhsldcyzzrcxxlupmmrcdcpucjldtaklwhgxavremlsclyntrvdirugcwyco",
        "egcuxjpcqscoskhpevmozvrorqyrgkubnfbjnmdizdfefyktjhyxnkdtmlynrhfbfvtkyqyzydmohbvzivnxuakaiypivnjzanut",
        "lgelwkgicsymdlfhzqmqjjzmvhgmfupexmkwfsritxjnlthvqdufbuxztnythjkjghgkcwurgaxnsnfsdojfpsduffsdvuhhxvyb",
        "sevckinmwdllzmyfukyhlfptjtevhjzpuwxlxsexboitoinyxqqrnhrpxxwtajkdfovniwhoxbcwcswvhrenibdtxtqaqgxucgmf",
        "bctothxokqfwmpoxszcfdvxdcgslszfdruojggudkbadjauicpxudrbvdpaztnratjgmjvfafaabenxikoyovhirzcanwbkddttz",
        "wdbwpurhwacqyzzkgxyeswegsamqlmkhedapnvgzwkoghxvcauswyubzgyvzdtzyeyqvlxhytdkdaaxbshfdnyjjhxojsmvyeszf",
        "erfvenulvwxffrnjgcaidxqsrartohnepquzndorzjfodhyvtauslbmaewoqbkglpdsbpioeqppvkzyoinrlcfdocjnusbathpdd",
        "dsmqsrbvfbwtaqdimttzwaryqfnzzuesnwlijzkqkljgazbobemdwcdublliadqxzphlflnegnhlebjknaqjhmhepksghmmlqwwy",
        "rrlrkdrfbchzmsbfxlacpbjurejdmjkqjdowyzvnvotspadebngzoyrgfexmitohfobppudfgwqepjwmvzvyrhofoljvvjcjdxxe",
        "lkyffzsxpfrloaicwyrzroapykalhlthlwtslwosfypuvdnvkqqaklnrimfsljhtxyubcohfuervzyfiewzstbxikctyplhkegwz",
        "vguuithogpkwstvojdjnibqcvxkzjfmwfeywwtirghblauypuuawgcgaryedznphdsdqtfgpfearicuomrvclkyauglwbpffjpxo",
        "xlafeqtzpmbmawdjpqqxyiufaanyfjakbbmbnlhvnniwmlkcbdtmudpxbehhqxxividslswujwxkjsnuklsoiuntpoeoththnbim",
        "dmlysvyuouancgiauwvblnvqllwzqrdlizistaykcxwphzexcopdlkkfckkzbwhkorieecibjlgzzvaksyiucazgxocvruufbysp",
        "rtkwbcbanblyeldendstkcdqkxuutmbdzlzxkzljprautvxlzbnmmbhjddaaxuxbjylhxsyszvcasgqdfeegrfythwdljxsjaxjm",
        "msndnzfqwolczhypynbcfhqyrawzmmemuerlasovycsmzpzrpwrqqbsvbvgclzstwnzocwgafurzcinhyfbyjasysrnbwrbtcuzt",
        "jfjpjjzffeysxaousnxhczcwrepafzqqqcimzcrthnxuiausoaspwmylrdwxodduzqqcyfrnkokqaywhzqgmkxaciewxweohmljn",
        "ppxjgcesomahdkkbaudnqjbgoqwdcdlxagkvvtdurrytddzahrlvzmezguzmjdmzbcumsboezywqqbhlcuadnavwcwxgxinznwds",
        "mahvqeqivnthszzbrjuvjfqgdeeogvydafogplfoafvmtzlnnqmmtrsjvamghlvcmyhfvrofvaxqeaxjfsetxyroqweaqiokaruk",
        "rtpitxjrgofvxwhjvsdkrepvzdzkzxaijzwmdgjtbwwexotawmnxgznhokuuzwlazjussravsgcjfrrwivnoxwnkbpiercmalpen",
        "gnhmficunrereknaxbsfewlcoeonqvjvthanjgwwblwccwjweadzbzpkjvtzumapichomaxtplpsftkqohmuvjrmyufvgyhuwrkg",
        "ifnkvtakgvdsiksqofqjudsivrrdxqsyqvmrxsghnqnkuzzfekpyhczqanxuqrbfrrtjjysiobkcxzycxvftqmivofazjzzydyxb",
        "fvsxzlemjgcioivfziicimgtvoxyuhxoxnpypnpenkprjwqzvugihhzqxwhtjgamuglaairkbiewkhtlogqqpqtzitqkiehdbkul",
        "prhuscstblsfwjdcviepnzrnwqvldjjxlyjyvgzahyzgphmhzqbwgyjguosuorojtghiotwkzvgpvevdmtptqlwcganacxaiwhcq",
        "gnmbjykwzovbmuowszohufsqjnroqjqsxsbshuhwdgdnbgtguilvzdjwgkxrzaqczjkmksnjoeoemiswvxxhbhuvginjsezfvuxx",
        "vtseqnbdygfxgsxlodfczhkdtspznaxyrlvhwfmexepwursoffqjsgtmnrysozusutewegqettsccccafdztmyssakpieldfhtlm",
        "jrymkhrigoofxlraalgesgrxgbanrmymdkowwgixnahgfssnsepcgwdwenaptzprdgbuhizdaqhfvpeseutsbrzpeublirtfzqgf",
        "ckxmapfuatkbihpojuxwdpggvmbkeylupjilukholcnzwprbjkdmoyirtqlqtwkkpfzvzmmyujpfxoyrlrwrfnueznokbczjdlgk",
        "npkceilxglgtdaytmvfzdrqlfxfgwkdngbxicwnzmonwpthndjqorarexwvjditimsuflwvvquilljopvnrpdvagozysfkfvudem",
        "rfjhfcjmfaejyoatvyuehkcmpoywipuwotqinnxgyfptviypfoqkqzsbgrrjmkjwtcebiolqtqwpgajvfwsvotcqsxibgpzifywa",
        "eqllshvdkxuxtymnfmfdbeexepilbkqfrqtngaznygqhufidkxhqkuyyidedfmmbejnvuoqlrdqrygwaxooonbvrhguxslqyirai",
        "sspskcbijbynzkwqrtoqrqrcvxjyhhrmxcqgvxksjbkdddghvmmhkiasjfhhtkjworwbfoperbzblldocqjdhhvybsutyjsojfbm",
        "ezqhyjmoeaqjrpmkxuazpoijyxrwfwgkjzjkuyqawhqbtnlrlnifvlggviuwujtqomoywzbnuflyjnuvkuykfczrxwyfczoenbcn",
        "ofnocgydgxrpeanernqdonsgxbykrvkifbdfarzryhjxjtsywbfknvwamftmdiwlhzybliyrvszlocpwhjcooqvxgytkbpykorte",
        "vahvqmlrewpqmioqvzvqmxhnmalpwauncybcqzdlouxtsmdfnnndntbfvwrxzoqfpghqwwiwrqaixszpogxeygrytsdrzymbnwad",
        "rlixgtxotirhzpkswuvdwzesnkvnbhdelyvdeyzuodosuxefkgljneypoellddeeixyfvluuzncmlvkcdaykohimazwuzdtrkmnb",
        "advednflhkrynkpcmmgnvtfkyzosjptpacmlfchypzavagrahqvivrwfhceazukpxzktymxynhacdjvexcrqrptkokexiahpiaop",
        "aaruoqyhttqnjkzsqdkvctfnhellamfnsgfddwjektcepdzmvrzpsfftoetpviogvhfpsflmtvaikntzhvpvafzpujdyjtppllhl",
        "cbobnpsdldxwqtuifrpirwjbwwcwnzotipuehojbrjyzhpxnkbkitsqooevlyzqsduppzssbfaiuppsykqilztbdgorvxfldmpbl",
        "badkppzteikostixbrqcobabuspwasfyohbetlpcbzwicgmiymlvxlhyqdjllrsciquzitrrabuvklmtccwcuakrxmmqwingjpnv",
        "ujkakbmrsszbrpowmertkccrfwzeqtxmyvqahksldvedmpeklczjytpohpxkahhksfdchdtgpiwrnblovviyrknmxfabduwbsdmy",
        "abpdumyljcukwwktbrkixxqjmbygvmukeazhdksxkwhupbydoepplailaibmclkonlxrqcjqgfhhxoegdvtdxuieyhzhshuiesmt",
        "npedgdohvuypwtuhhohhnglkwponltfwytlftzgdzzxffdodgbemquikpoqnbsptkstbfitkcvtpdzlyhxrgvppghpyrrftdkyjw",
        "ojjvmuhzmeyzlhciposvyrjhxmnixatybjtubxvywdoegkrzmpicfnoguwxvdpneyjcylhcfiizhrxhpozyzcluuzdpcoanehqxu",
        "zwjoixuxwbcxqeckxvkwqgpkmwanwqaurirfnfnukjqwvcdmfftdzeftrpornkgpbmxtwvkulqblftmocstflblklfvcyjzbpuca",
        "taszycvnlzdpcvqdsotjpgcbhidjwgdjmrinbklthrreomcpuctiqkskgpubhihklwgloryikfechymwlzbfrwjysvjudtdtggkq",
        "buxfguqktkgmqwunjsvpprudmreyeienogwoswnkpxbtjvtkefcaodxkemlwjylbovslibkqyzkeyqibxxthkbsggkffxggketfp",
        "idsngzcyugggoohnkwllwhuurlyegxqrgmvofgybccvfypmdabdmnszqpkghsbtzlozkrcrdapjsgsczpiyzvunkdpesisduxnfs",
        "lrcejrfhfijbnqmrhwfahwmacjbcwgrgmbesuwaxnuacovcrfhpdkfuurjlnonzjvtjogxrphfzaulvpmbuniklwercpukylqokq"
        ];

    let start = Instant::now();
    for time in 0..10 {
        for count in 0..sub_strings.len() {
            println!("{time} - {count} for {} was {}", sub_strings[count], find_substring_rabin_karp_algorithm(&string, &sub_strings[count].to_string()));
        }
    }

    let duration = start.elapsed();
    println!("Time: {:?}", duration);
}
