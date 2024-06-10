/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a lookup table for n! at double precision.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 18, 2022                                              *
 ******************************************************************************/

/*  The lookup table is declared here.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we use a much larger table. n! is pre-computed for  *
 *  every non-negative integer that does not overflow, 0 <= n <= 170.         */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Lookup table for the factorial function.                                  */
const double tmpl_double_factorial_table[171] = {
    1.000000000000000000000000000000e+00,
    1.000000000000000000000000000000e+00,
    2.000000000000000000000000000000e+00,
    6.000000000000000000000000000000e+00,
    2.400000000000000000000000000000e+01,
    1.200000000000000000000000000000e+02,
    7.200000000000000000000000000000e+02,
    5.040000000000000000000000000000e+03,
    4.032000000000000000000000000000e+04,
    3.628800000000000000000000000000e+05,
    3.628800000000000000000000000000e+06,
    3.991680000000000000000000000000e+07,
    4.790016000000000000000000000000e+08,
    6.227020800000000000000000000000e+09,
    8.717829120000000000000000000000e+10,
    1.307674368000000000000000000000e+12,
    2.092278988800000000000000000000e+13,
    3.556874280960000000000000000000e+14,
    6.402373705728000000000000000000e+15,
    1.216451004088320000000000000000e+17,
    2.432902008176640000000000000000e+18,
    5.109094217170944000000000000000e+19,
    1.124000727777607680000000000000e+21,
    2.585201673888497821286400000000e+22,
    6.204484017332394099998720000000e+23,
    1.551121004333098605530316800000e+25,
    4.032914611266056503227842560000e+26,
    1.088886945041835194023988428800e+28,
    3.048883446117138719189028044800e+29,
    8.841761993739701898620088352768e+30,
    2.652528598121910682176017190093e+32,
    8.222838654177922430198509928972e+33,
    2.631308369336935177663523177271e+35,
    8.683317618811885938715673895318e+36,
    2.952327990396041573340815339632e+38,
    1.033314796638614543113498996280e+40,
    3.719933267899012548636727524947e+41,
    1.376375309122634557887211483361e+43,
    5.230226174666011171418598922525e+44,
    2.039788208119744412312967339770e+46,
    8.159152832478976837955485213012e+47,
    3.345252661316380795628447229919e+49,
    1.405006117752879954933135270705e+51,
    6.041526306337383407444082928558e+52,
    2.658271574788448869416579949035e+54,
    1.196222208654801885749927231575e+56,
    5.502622159812089153567237889925e+57,
    2.586232415111681776734910066530e+59,
    1.241391559253607252832756831934e+61,
    6.082818640342675224886016081167e+62,
    3.041409320171337557636696640675e+64,
    1.551118753287382189470754582686e+66,
    8.065817517094387684563459155335e+67,
    4.274883284060025484791254765342e+69,
    2.308436973392413792437188390603e+71,
    1.269640335365827644688282384082e+73,
    7.109985878048634810254381350857e+74,
    4.052691950487721409980397975385e+76,
    2.350561331282878494921656950155e+78,
    1.386831185456898386051482680046e+80,
    8.320987112741389895059729406045e+81,
    5.075802138772248358335401613731e+83,
    3.146997326038793939032034333072e+85,
    1.982608315404440084965732774768e+87,
    1.268869321858841654378068975851e+89,
    8.247650592082471516735380327295e+90,
    5.443449390774430694454960602756e+92,
    3.647111091818868322121436205483e+94,
    2.480035542436830547970901153987e+96,
    1.711224524281412973757354342721e+98,
    1.197857166996989221259474668629e+100,
    8.504785885678623004701736013089e+101,
    6.123445837688608463920602647467e+103,
    4.470115461512684385548506279122e+105,
    3.307885441519386241602297013102e+107,
    2.480914081139539974534903351992e+109,
    1.885494701666050380646526547514e+111,
    1.451830920282858721008262979255e+113,
    1.132428117820629679353591854775e+115,
    8.946182130782975713626288779037e+116,
    7.156945704626380570901031023229e+118,
    5.797126020747367841357823599388e+120,
    4.753643337012842019808180069811e+122,
    3.945523969720658788370442603924e+124,
    3.314240134565353194347765165390e+126,
    2.817104114380550131023834223967e+128,
    2.422709538367273412812966506710e+130,
    2.107757298379527854371528537190e+132,
    1.854826422573984360543241318572e+134,
    1.650795516090846024396768690378e+136,
    1.485715964481761514918087432469e+138,
    1.352001527678402915775142528473e+140,
    1.243841405464130817897393534438e+142,
    1.156772507081641565875592301258e+144,
    1.087366156656743075388893880833e+146,
    1.032997848823905930491992207978e+148,
    9.916779348709496478448922511836e+149,
    9.619275968248212038369657521235e+151,
    9.426890448883247983672977790486e+153,
    9.332621544394415325208363129692e+155,
    9.332621544394415096564670479595e+157,
    9.425947759838359881635491467327e+159,
    9.614466715035127079268201296674e+161,
    9.902900716486180472083242173105e+163,
    1.029901674514562810014039784705e+166,
    1.081396758240290976701866637109e+168,
    1.146280563734708368264938985623e+170,
    1.226520203196138004993154848398e+172,
    1.324641819451829017933416595747e+174,
    1.443859583202493662498452857992e+176,
    1.588245541522743028748298143791e+178,
    1.762952551090244587352755711332e+180,
    1.974506857221074011545290006487e+182,
    2.231192748659813765724544204963e+184,
    2.543559733472187655186356145442e+186,
    2.925093693493015996691185718122e+188,
    3.393108684451898086234012634122e+190,
    3.969937160808721061647562973218e+192,
    4.684525849754290923658697018766e+194,
    5.574585761207605823104001022492e+196,
    6.689502913449127120509299431182e+198,
    8.094298525273444092008008576449e+200,
    9.875044200833601058004609193369e+202,
    1.214630436702532930134566930784e+205,
    1.506141741511140931388048138400e+207,
    1.882677176888926112907603224750e+209,
    2.372173242880046851164245145816e+211,
    3.012660018457659430899503448509e+213,
    3.856204823625804071551364414092e+215,
    4.974504222477287458972899762535e+217,
    6.466855489220474147362034271772e+219,
    8.471580690878820631398613884709e+221,
    1.118248651196004329765681365726e+224,
    1.487270706090685713384063312485e+226,
    1.992942746161518792813014020149e+228,
    2.690472707318050407328925674102e+230,
    3.659042881952548864222778716265e+232,
    5.012888748274991960532163630589e+234,
    6.917786472619488580772780558768e+236,
    9.615723196941089353195281673345e+238,
    1.346201247571752574223442013534e+241,
    1.898143759076170889798399117002e+243,
    2.695364137888162853030095435194e+245,
    3.854370717180073078749417048356e+247,
    5.550293832739304438509897291670e+249,
    8.047926057471991706101700580629e+251,
    1.174997204390910709729104241097e+254,
    1.727245890454638923025609745627e+256,
    2.556323917872865392701440571373e+258,
    3.808922637630569789330073125924e+260,
    5.713383956445854683995109688885e+262,
    8.627209774233239985511343864617e+264,
    1.311335885683452449158820348947e+267,
    2.006343905095682295326353716927e+269,
    3.089769613847350775859317381593e+271,
    4.789142901463394077957783381704e+273,
    7.471062926282894223475335786737e+275,
    1.172956879426414474267710495788e+278,
    1.853271869493734989000452470811e+280,
    2.946702272495038402768377244653e+282,
    4.714723635992061609521444571341e+284,
    7.590705053947218993219076583984e+286,
    1.229694218739449417732502919411e+289,
    2.004401576545302626640283742249e+291,
    3.287218585534295908841049615608e+293,
    5.423910666131588675026681968879e+295,
    9.003691705778437545433467618605e+297,
    1.503616514864999145599966475945e+300,
    2.526075744973198421854320465720e+302,
    4.269068009004705108334767730582e+304,
    7.257415615307999035000409552389e+306
};

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  For the portable method we pre-compute n! for all non-negative integers   *
 *  n such that n! < 10^38. This is 0 <= n <= 33.                             */

/*  Lookup table for the factorial function.                                  */
const double tmpl_double_factorial_table[34] = {
    1.000000000000000000000000000000e+00,
    1.000000000000000000000000000000e+00,
    2.000000000000000000000000000000e+00,
    6.000000000000000000000000000000e+00,
    2.400000000000000000000000000000e+01,
    1.200000000000000000000000000000e+02,
    7.200000000000000000000000000000e+02,
    5.040000000000000000000000000000e+03,
    4.032000000000000000000000000000e+04,
    3.628800000000000000000000000000e+05,
    3.628800000000000000000000000000e+06,
    3.991680000000000000000000000000e+07,
    4.790016000000000000000000000000e+08,
    6.227020800000000000000000000000e+09,
    8.717829120000000000000000000000e+10,
    1.307674368000000000000000000000e+12,
    2.092278988800000000000000000000e+13,
    3.556874280960000000000000000000e+14,
    6.402373705728000000000000000000e+15,
    1.216451004088320000000000000000e+17,
    2.432902008176640000000000000000e+18,
    5.109094217170944000000000000000e+19,
    1.124000727777607680000000000000e+21,
    2.585201673888497821286400000000e+22,
    6.204484017332394099998720000000e+23,
    1.551121004333098605530316800000e+25,
    4.032914611266056503227842560000e+26,
    1.088886945041835194023988428800e+28,
    3.048883446117138719189028044800e+29,
    8.841761993739701898620088352768e+30,
    2.652528598121910682176017190093e+32,
    8.222838654177922430198509928972e+33,
    2.631308369336935177663523177271e+35,
    8.683317618811885938715673895318e+36
};

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */