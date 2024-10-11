
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
 ******************************************************************************/

/*  Declaration given here.                                                   */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Remez coefficients for the Normalized Fresnel sine function on [1, 2].    */
const float tmpl_float_normalized_fresnel_sin_table[128] = {
    +4.3825915620326468049947166411967193099119308589313E-01F,
    +9.9999093336481210394976757562184351640500392283134E-01F,
    +1.4586345691168791032362125176638211090926204981033E-03F,
    -1.7202832910010489297862595916703741146850836697282E+00F,
    +4.6945779739971647341954983116504795810292405297024E-01F,
    +9.9502510895783775904234549074674820711993503598279E-01F,
    -1.5994351519634627601459488313048752197996106137392E-01F,
    -1.8605668664297841156013386501541724104925022548759E+00F,
    +5.0033935585097445530040527743954769782450172753193E-01F,
    +9.7956299690334664611648930448000637390779196256150E-01F,
    -3.3454036369540121569961338753585197571156947573718E-01F,
    -1.9817620841405576621120558519501074342829043370937E+00F,
    +5.3056351963101194803104217595517283640706332900376E-01F,
    +9.5283656937879755563018409515357555108147062012717E-01F,
    -5.2054518716530158444689884000247350117054906676916E-01F,
    -2.0779825098349933095356090577110210092413504308124E+00F,
    +5.5976790044054232635620649574681257971274486595811E-01F,
    +9.1420675193628948971780724147241189013549396425736E-01F,
    -7.1561837890852438733006089420104976236575433841967E-01F,
    -2.1430273135321456459089935876961697858845988248591E+00F,
    +5.8757261294967768285512216525329919274473873186316E-01F,
    +8.6319886853688620589270545346559605948786188262515E-01F,
    -9.1683691209710617599959791223573043944780012413496E-01F,
    -2.1705451643193938000870001908311572430859736193761E+00F,
    +6.1358598641508463290741783898983288257037752287256E-01F,
    +7.9953957986187234103018418120368881529914515630644E-01F,
    -1.1206829553863138317630193961010001948185404228855E+00F,
    -2.1541645396162281374086223682730743550892593084273E+00F,
    +6.3741143833109032033951119303999694284621343753857E-01F,
    +7.2319400448033285657323918140308235368666532764111E-01F,
    -1.3230375672875284604379395111532630846436317805681E+00F,
    -2.0878477990601699626477677937377823138104437296826E+00F,
    +6.5865550263105584978376886290038223829076295838076E-01F,
    +6.3440232269473115298946325307799796115162344139273E-01F,
    -1.5192138593377310501894304045175997684294700849449E+00F,
    -1.9660407495861573894587929573252638369904253922017E+00F,
    +6.7693696549963003890772481756786071295884893393942E-01F,
    +5.3371382206107313822139293743606192297633174492646E-01F,
    -1.7040018886904703958744387723644647487829095855539E+00F,
    -1.7840389136363504759624002992755366498006644232515E+00F,
    +6.9189700978012618191051970027974893996937920655749E-01F,
    +4.2201704963904819110450304383381217082065934118836E-01F,
    -1.8717480432110919991824740561248387956144750165929E+00F,
    -1.5383141318314891367327925885311767831055863680798E+00F,
    +7.0321021420884924023864940288025287542406538146073E-01F,
    +3.0056405193523793313126294201041044630688009428939E-01F,
    -2.0164651746078310847731709366101885438009755658072E+00F,
    -1.2268736566258331431976969690226481495233616445351E+00F,
    +7.1059619163484115248763047197527884671806983858420E-01F,
    +1.7098667776528091606194235970707761602357644642962E-01F,
    -2.1319765236606917801540853546310895607367235323299E+00F,
    -8.4962920833819155637135353176535389420690442380553E-01F,
    +7.1383158488821967260551856925915538625061807423150E-01F,
    +3.5302805230419422019502510628859040866060905987332E-02F,
    -2.2120943786467744669069278943585766448874403909110E+00F,
    -4.0876032478079582195433351383228205822445269541671E-01F,
    +7.1276207168059884334293116276328024089824834739384E-01F,
    -1.0408965893683492812307604508378377992558069616680E-01F,
    -2.2508329569717420759347185447918032954576298946137E+00F,
    +9.0946977510856336729780444425785076368811983944130E-02F,
    +7.0731396375633435298678229462634383195906497290877E-01F,
    -2.4443307158988962990549123208275251645327767727173E-01F,
    -2.2426532159848748302743003712252924187221296117136E+00F,
    +6.4180843757597712955129308006614277264530070477173E-01F,
    +6.9750492393334191676333706483698066564302795999077E-01F,
    -3.8264649198409933259783158048699139626180702308531E-01F,
    -2.1827352142026655911874310490759194738398581175955E+00F,
    +1.2330220294372122375064992384021716634719900677099E+00F,
    +6.8345327175233163393310671123529163934655499221662E-01F,
    -5.1537977408903275264886955051279374644071171196476E-01F,
    -2.0672712716544457815486516972871173766718846335053E+00F,
    +1.8505480312391701481831984368102173219865662361187E+00F,
    +6.6538530879024970503422675620073379231956145907190E-01F,
    -6.3908631728679776414141934244435696481327570537789E-01F,
    -1.8937705867769833576203445871031301717840300015732E+00F,
    +2.4771167148357676810828758562551026082631817437989E+00F,
    +6.4364007327001039486329105913642880812477948503226E-01F,
    -7.5011481398715719885398715568909162995510372910054E-01F,
    -1.6613633347494612944723631985310445764197451672035E+00F,
    +3.0923920525194763636014020873639163377550343917146E+00F,
    +6.1867093558086862639568908693280181759962051022731E-01F,
    -8.4481950164998465008680841244454718731946064296880E-01F,
    -1.3710896011041653697423688516604242682971524798421E+00F,
    +3.6733169092905956672618728250591093210929801595286E+00F,
    +5.9104347679471186123293384486577888901459500131123E-01F,
    -9.1968743709785240876129427739397536936843280175129E-01F,
    -1.0261560934847763688367804744023909071124239163143E+00F,
    +4.1946610742036798238353105120519138843407869757403E+00F,
    +5.6142915588892991402252013720366271526759182487115E-01F,
    -9.7148018325807750273872015468017838589076545163302E-01F,
    -6.3214154929065180603646435049099976115041305945150E-01F,
    +4.6297863590470678490543695419156832225276638644064E+00F,
    +5.3059437201335343169277143748666358718688597241190E-01F,
    -9.9738606484993394976399907728941098309095118611112E-01F,
    -1.9713041881824825185186011376699558962327233303700E-01F,
    +4.9516339616431139503868402667384744362686116714945E+00F,
    +4.9938466833823086375388917194425788074004924386039E-01F,
    -9.9517785597446244502296484158082004730196222540746E-01F,
    +2.6824592242440521018411124166292411590392487644383E-01F,
    +5.1339283027075179602066946094936998058701655515403E+00F,
    +4.6870400485923077541943031335669565780910476030245E-01F,
    -9.6336954111284448702844597639026259221587016002946E-01F,
    +7.5088282520267151806876479492024110507749394484043E-01F,
    +5.1525654219037872431443096953734123921552156522902E+00F,
    +4.3948924590953177059519950882312699451401283040568E-01F,
    -9.0136428048746264914557291735788865567553518420307E-01F,
    +1.2354008372402421696375702706218023224026347231449E+00F,
    +4.9871465695120618102483249122360237392779220103507E+00F,
    +4.1268026594261963427070347755687246253671014173307E-01F,
    -8.0958551446627707769847168444828189781419678739492E-01F,
    +1.7044992105436542931127648853426746849748172868555E+00F,
    +4.6226716642879387151732330268479821798368141060032E+00F,
    +3.8918635354558797506287401369262303428026486806572E-01F,
    -6.8958112412144951276224221178527816313996017529327E-01F,
    +2.1394560319555180599716996246637372183996137194796E+00F,
    +4.0511303031248719029597219447791036212404112933065E+00F,
    +3.6984989839204715875835424047386982401804185765563E-01F,
    -5.4409151662316831799214511065315771325822667056719E-01F,
    +2.5207876758859577504261225783293252262982081660969E+00F,
    +3.2731151143459812570883408070103959766617436653704E+00F,
    +3.5540864347153302649194813521660252025762463027915E-01F,
    -3.7707187174179404267449376944070152047266973700823E-01F,
    +2.8290567082734531167756765560193627438035731750135E+00F,
    +2.2991995731630315698044648143885029568469507604549E+00F,
    +3.4645807316758429135031227720205471889309193189448E-01F,
    -1.9365988561080897747037190492409482090483000538042E-01F,
    +3.0458105032526007649377326142775587989366278215476E+00F,
    +1.1510042771453337342571069230251431589310104184835E+00F
};