/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LAMBERTW_PADE_LDOUBLE_H
#define TMPL_LAMBERTW_PADE_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P01 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define P02 (+1.0682502565416050016723105546359160380709861862124E+01L)
#define P03 (+4.6571964665591139713188203885880491905853395796878E+01L)
#define P04 (+1.0645221196874087589402765839192190487117781040351E+02L)
#define P05 (+1.3621315458647873063125988415924999885445238071605E+02L)
#define P06 (+9.6194426795076224947202936312211557831255938423266E+01L)
#define P07 (+3.4212690660831692810057957056825594180703795525921E+01L)
#define P08 (+4.7902915867548580879769213470489619147298431970733E+00L)
#define P09 (+8.7004781328169727922261553430157539405962610146625E-02L)
#define P10 (-2.3526462504008900307253829870553999017908603231409E-03L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (+1.1682502565416050016723105546359160380709861862124E+01L)
#define Q02 (+5.6754467231007189729911309432239652286563257659002E+01L)
#define Q03 (+1.4834959201829065726552097617128948325334294193599E+02L)
#define Q04 (+2.2537605259936807001317551097247109802651006779587E+02L)
#define Q05 (+2.0034496978815222117142763345976687675905641654059E+02L)
#define Q06 (+9.9324282254815566451544174900199633472503607783434E+01L)
#define Q07 (+2.4201439090875344909012382876194017492323387287572E+01L)
#define Q08 (+2.0878375944665185359069024322498319401797520687138E+00L)

/*  Helper macros for evaluating the polynomials via Horner's method.         */
#define TMPL_NUM_EVAL(z) \
z*(P01+z*(P02+z*(P03+z*(P04+z*(P05+z*(P06+z*(P07+z*(P08+z*(P09+z*P10)))))))))

#define TMPL_DEN_EVAL(z) \
Q00+z*(Q01+z*(Q02+z*(Q03+z*(Q04+z*(Q05+z*(Q06+z*(Q07+z*Q08)))))))

/*  128-bit double-double, a few more terms.                                  */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P01 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define P02 (+2.3050016060106838425132893353378047376456990886110E+01L)
#define P03 (+2.4260928650054595925713015374542235310832698738570E+02L)
#define P04 (+1.5442089342101045324301751356739311897908266742798E+03L)
#define P05 (+6.6351199913091933376224001869217612548518845073448E+03L)
#define P06 (+2.0345404534483236469837658976128348296108215462279E+04L)
#define P07 (+4.5891652165933122312037940080953005694074521327858E+04L)
#define P08 (+7.7357454508887737024367650140465091434313668498714E+04L)
#define P09 (+9.8010901099214829900539332550667955268364257324601E+04L)
#define P10 (+9.3116808255866153779884706838635735978493592175454E+04L)
#define P11 (+6.5673065073161058431931116137448333921622839665350E+04L)
#define P12 (+3.3749828623891909387105551372937047421461840563066E+04L)
#define P13 (+1.2272521675127128457674014889642116282369975121794E+04L)
#define P14 (+3.0201191029032556545246650245456459533732054089017E+03L)
#define P15 (+4.6960806400195513755243880068198040333497335331220E+02L)
#define P16 (+4.1248634293272872078919729669038149890409819889458E+01L)
#define P17 (+1.6657256026854926189105852213238515427944946296529E+00L)
#define P18 (+1.8969197591707029016827639166414014394215520475438E-02L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (+2.4050016060106838425132893353378047376456990886110E+01L)
#define Q02 (+2.6515930256065279768226304709880040048478397827181E+02L)
#define Q03 (+1.7759598793472637391414055094093311858775918328891E+03L)
#define Q04 (+8.0722659596424294493740988412918999663395190151891E+03L)
#define Q05 (+2.6346361648286787987521450526020875221505057175994E+04L)
#define Q06 (+6.3720866970072501074716083359148922731995808261288E+04L)
#define Q07 (+1.1618936283237420736714450934044748733042318522921E+05L)
#define Q08 (+1.6095589537391943712639556152324088201371521113482E+05L)
#define Q09 (+1.6942876545689912721447430539792830496726892032417E+05L)
#define Q10 (+1.3463176260342851029869056106954498799651827716449E+05L)
#define Q11 (+7.9663274061031213402634803624643809680357586654131E+04L)
#define Q12 (+3.4336435725087988195170617155899877897947512599368E+04L)
#define Q13 (+1.0429681179537777002051198981995139636859813089883E+04L)
#define Q14 (+2.1252502497325923310095141271276406011582292361323E+03L)
#define Q15 (+2.6937440958319112320374078488139826705291070216499E+02L)
#define Q16 (+1.8757876173858948749882355583340471125658233755736E+01L)
#define Q17 (+5.6855586900772720284704578097027263337106858382372E-01L)
#define Q18 (+4.1961127363331396660758702572371028427828324320444E-03L)

/*  Helper macros for evaluating the polynomials via Horner's method.         */
#define TMPL_NUM_EVAL(z) \
z*(\
  P01 + z*(\
    P02 + z*(\
      P03 + z*(\
        P04 + z*(\
          P05 + z*(\
            P06 + z*(\
              P07 + z*(\
                P08 + z*(\
                  P09 + z*(\
                    P10 + z*(\
                      P11 + z*(\
                        P12 + z*(\
                          P13 + z*(\
                            P14 + z*(\
                              P15 + z*(\
                                P16 + z*(\
                                  P17 + z*P18\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
  Q01 + z*(\
    Q02 + z*(\
      Q03 + z*(\
        Q04 + z*(\
          Q05 + z*(\
            Q06 + z*(\
              Q07 + z*(\
                Q08 + z*(\
                  Q09 + z*(\
                    Q10 + z*(\
                      Q11 + z*(\
                        Q12 + z*(\
                          Q13 + z*(\
                            Q14 + z*(\
                              Q15 + z*(\
                                Q16 + z*(\
                                  Q17 + z*Q18\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  128-bit quadruple, even more terms.                                       */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P01 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define P02 (+2.4340947816621764974820901248816032548700314820727E+01L)
#define P03 (+2.7185827502137480614779742004438139787018451681301E+02L)
#define P04 (+1.8463735801285887739871791980260908500839221588184E+03L)
#define P05 (+8.5196682087947186254664843204162459199135819337663E+03L)
#define P06 (+2.8264422584611709901263124197565557493169123020219E+04L)
#define P07 (+6.9585103840037283975839245992365810168927093490769E+04L)
#define P08 (+1.2936657969602153153031114798328222160006762542498E+05L)
#define P09 (+1.8305687519733867092220110564947749143324050146383E+05L)
#define P10 (+1.9724337661999766203553813821995304655051577699606E+05L)
#define P11 (+1.6081802419847108287086418808505610869665285691228E+05L)
#define P12 (+9.7899704578656392983501558241216365389223024010564E+04L)
#define P13 (+4.3540015496620094149994590829164652814079856473083E+04L)
#define P14 (+1.3687111463098407610245974351752661222940069888064E+04L)
#define P15 (+2.8932731181403961289378301558697458039764964480357E+03L)
#define P16 (+3.8026700353231284784666959950544243761900126078378E+02L)
#define P17 (+2.7145380318146117803174116840234522462551770573271E+01L)
#define P18 (+7.9005584685768145571704039802876923994159262608600E-01L)
#define P19 (+2.5467659039996142412799322850753162338486651989280E-03L)
#define P20 (-1.6955161664265747013213983777656250921345406502478E-05L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (+2.5340947816621764974820901248816032548700314820727E+01L)
#define Q02 (+2.9569922283799657112261832129319743041888483163374E+02L)
#define Q03 (+2.1067280479083193643142328341127308983464231848877E+03L)
#define Q04 (+1.0245214949957034506362978742586023426094878710725E+04L)
#define Q05 (+3.6016892620396017858237877018426760883336912364945E+04L)
#define Q06 (+9.4562354558502662410946148875743739287917532295743E+04L)
#define Q07 (+1.8890565575997565441264918741442279057178142748401E+05L)
#define Q08 (+2.8985311696028830815148577693606700742650776475018E+05L)
#define Q09 (+3.4243677006123885068844521867228992016346742053238E+05L)
#define Q10 (+3.1037181239034623602736171436261710253423949515967E+05L)
#define Q11 (+2.1374539411414217019484369596301097744783367636107E+05L)
#define Q12 (+1.1002504949606748718979706933008620516530346232151E+05L)
#define Q13 (+4.1288446830701383826347313165171495674469771793480E+04L)
#define Q14 (+1.0886978294115901071396031198242511523542421954164E+04L)
#define Q15 (+1.9087919588872583808674100179071702278258087167505E+03L)
#define Q16 (+2.0394449546951252059732520905664995368612962393314E+02L)
#define Q17 (+1.1385140065772375344197106030138088206162683389698E+01L)
#define Q18 (+2.3433248868992686000033679349385810012794190102041E-01L)

/*  Helper macros for evaluating the polynomials via Horner's method.         */
#define TMPL_NUM_EVAL(z) \
z*(\
  P01 + z*(\
    P02 + z*(\
      P03 + z*(\
        P04 + z*(\
          P05 + z*(\
            P06 + z*(\
              P07 + z*(\
                P08 + z*(\
                  P09 + z*(\
                    P10 + z*(\
                      P11 + z*(\
                        P12 + z*(\
                          P13 + z*(\
                            P14 + z*(\
                              P15 + z*(\
                                P16 + z*(\
                                  P17 + z*(\
                                    P18 + z*(\
                                      P19 + z*P20\
                                    )\
                                  )\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
  Q01 + z*(\
    Q02 + z*(\
      Q03 + z*(\
        Q04 + z*(\
          Q05 + z*(\
            Q06 + z*(\
              Q07 + z*(\
                Q08 + z*(\
                  Q09 + z*(\
                    Q10 + z*(\
                      Q11 + z*(\
                        Q12 + z*(\
                          Q13 + z*(\
                            Q14 + z*(\
                              Q15 + z*(\
                                Q16 + z*(\
                                  Q17 + z*Q18\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  80-bit extended and portable.                                             */
#else

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P01 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define P02 (+1.3423587113873572799856418256917291722636165064827E+01L)
#define P03 (+7.6825399878452118211023886601382620764816989245488E+01L)
#define P04 (+2.4449342305115819095532775127435940770146781415298E+02L)
#define P05 (+4.7308412847398645709936992582794212677408807333724E+02L)
#define P06 (+5.7148125201182976230129836041522479211056878643278E+02L)
#define P07 (+4.2557379987922342457880859105073834369967419989466E+02L)
#define P08 (+1.8544028195454201677063968427282053306935617630759E+02L)
#define P09 (+4.2179995530871901889710190535734136872923223300049E+01L)
#define P10 (+3.8466440189684608921657256842964664276984124873344E+00L)
#define P11 (+4.3777951491984315669652523334245331137700687845106E-02L)
#define P12 (-8.1685878112431124096627982633678306229341576140402E-04L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (+1.4423587113873572799856418256917291722636165064827E+01L)
#define Q02 (+8.9748986992325691010880304858299912487453154310315E+01L)
#define Q03 (+3.1527369603934018943309009541395004927163338753272E+02L)
#define Q04 (+6.8698890966183430414909001263955508524157150291070E+02L)
#define Q05 (+9.6056740004276409999718186446787700902250192649259E+02L)
#define Q06 (+8.6137673622339263017515453147865534042760442055349E+02L)
#define Q07 (+4.8049700629405300526729994440647582323840066110890E+02L)
#define Q08 (+1.5558251762557263998494806421217838056656034765323E+02L)
#define Q09 (+2.5420840655542739222839031493346480281754609315400E+01L)
#define Q10 (+1.4954871377483368720556434342908260479536376434936E+00L)

/*  Helper macros for evaluating the polynomials via Horner's method.         */
#define TMPL_NUM_EVAL(z) \
z*(\
  P01 + z*(\
    P02 + z*(\
      P03 + z*(\
        P04 + z*(\
          P05 + z*(\
            P06 + z*(\
              P07 + z*(\
                P08 + z*(\
                  P09 + z*(\
                    P10 + z*(\
                      P11 + z*P12\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
  Q01 + z*(\
    Q02 + z*(\
      Q03 + z*(\
        Q04 + z*(\
          Q05 + z*(\
            Q06 + z*(\
              Q07 + z*(\
                Q08 + z*(\
                  Q09 + z*Q10\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

#endif
/*  End of double vs extended vs double-double vs quadruple coefficients.     */

/*  Function for computing the Lambert W function via a Pade approximant.     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_LambertW_Pade(long double x)
{
    /*  Use the helper functions to evaluate the numerator and denominator.   */
    const long double p = TMPL_NUM_EVAL(x);
    const long double q = TMPL_DEN_EVAL(x);
    return p/q;
}
/*  End of tmpl_LDouble_LambertW_Pade.                                        */

/*  Undefine everything in case someone wants to #include this file.          */
#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef P08
#undef P09
#undef P10
#undef P11
#undef P12
#undef P13
#undef P14
#undef P15
#undef P16
#undef P17
#undef P18
#undef P19
#undef P20
#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08
#undef Q09
#undef Q10
#undef Q11
#undef Q12
#undef Q13
#undef Q14
#undef Q15
#undef Q16
#undef Q17
#undef Q18
#undef Q19
#undef Q20
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of include guard.                                                     */
