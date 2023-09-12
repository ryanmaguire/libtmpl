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

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CBRT_TABLE_DOUBLE_H
#define TMPL_CBRT_TABLE_DOUBLE_H

/*  The values cbrt(1 + k/128) for k = 0, 1, ..., 126, 127.                   */
static const double tmpl_double_cbrt_table[128] = {
    1.0000000000000000000000000000000, 1.0025974142646002445641810219251,
    1.0051814396472644940216361286079, 1.0077522473643225547531221593643,
    1.0103100051555475677004975186586, 1.0128548773804866675475088668966,
    1.0153870251114199472705153964498, 1.0179066062230899643192835511298,
    1.0204137754793370176414454033065, 1.0229086846167688117779793730487,
    1.0253914824255868804617962455355, 1.0278623148276862444158197280055,
    1.0303213249521392048443722793416, 1.0327686532081689053986600606709,
    1.0352044373557133125011297023314, 1.0376288125736755494301153185484,
    1.0400419115259520572650284121789, 1.0424438644253258305299813331824,
    1.0448347990953079730140940872272, 1.0472148410300070265876039863363,
    1.0495841134521019305383246481663, 1.0519427373689910594909927770260,
    1.0542908316271865535571371892576, 1.0566285129650200849034033336674,
    1.0589558960637232909745381060545, 1.0612730935969433373157816981626,
    1.0635802162787514440183421655311, 1.0658773729101997114903243952323,
    1.0681646704244792062469321323106, 1.0704422139307300088815492517690,
    1.0727101067565517779070785583636, 1.0749684504892613387200716047905,
    1.0772173450159418608796467832597, 1.0794568885623263338910985399200,
    1.0816871777305562867412287330851, 1.0839083075358550148472712375198,
    1.0861203714421529754305876365136, 1.0883234613967014844470426559062,
    1.0905176678637093911784948691690, 1.0927030798570360167223371961119,
    1.0948797849719723164299508828431, 1.0970478694161409605615204997782,
    1.0992074180395448189523026981346, 1.1013585143637921814080145318314,
    1.1035012406105259431129103596633, 1.1056356777290829309461032498228,
    1.1077619054234085398073632889972, 1.1098800021782508855365861940661,
    1.1119900452846577605826816883611, 1.1140921108647987981690823586204,
    1.1161862738961344083584921202686, 1.1182726082349522432889772842143,
    1.1203511866392911771868705035096, 1.1224220807912720479028475840938,
    1.1244853613188536990978901985768, 1.1265410978170321843407408496362,
    1.1285893588685003448612656756661, 1.1306302120637843502020093130867,
    1.1326637240208731942598194251101, 1.1346899604043565670129440911379,
    1.1367089859440859734504803853303, 1.1387208644533734447828035919396,
    1.1407256588467416818909839765751, 1.1427234311572389861994923911088,
    1.1447142425533318678080422119397, 1.1466981533553877739198725482300,
    1.1486752230517599515235741161056, 1.1506455103144860461334884503723,
    1.1526090730146116424186740244852, 1.1545659682371495720383124605517,
    1.1565162522956854482730905924478, 1.1584599807466395354515076137057,
    1.1603972084031947231025190877299, 1.1623279893489000496364014611865,
    1.1642523769509589076072526412113, 1.1661704238732107617127964804177,
    1.1680821820888149211350055787562, 1.1699877028926446291372689373998,
    1.1718870369133994645518358669049, 1.1737802341254437914779769778665,
    1.1756673438603787447500081699785, 1.1775484148183549991276512210927,
    1.1794234950791333393301323359957, 1.1812926321128998256183452161415,
    1.1831558727908421352812658600906, 1.1850132633954934537742500850417,
    1.1868648496308500900734435322338, 1.1887106766322687987520409685971,
    1.1905507889761496060637792294542, 1.1923852306894097586628826691946,
    1.1942140452587542412359333662832, 1.1960372756397481430196324621974,
    1.1978549642656959926900021618350, 1.1996671530563330262045908935440,
    1.2014738834263332026410145965253, 1.2032751962936386386935304736870,
    1.2050711320876149930641848338016, 1.2068617307570371973249159805438,
    1.2086470317779097997485535323917, 1.2104270741611260629344918698729,
    1.2122018964599698346209428535405, 1.2139715367774640937192187140860,
    1.2157360327735699601723683945382, 1.2174954216722398475830650255974,
    1.2192497402683283315324629316265, 1.2209990249343642039872395530485,
    1.2227433116271870850362574853643, 1.2244826358944518672866319590649,
    1.2262170328810041754619949364720, 1.2279465373351299339688209355567,
    1.2296711836146820483199013553121, 1.2313910056930871222219615234699,
    1.2331060371652350507458056615773, 1.2348163112532542512051178446185,
    1.2365218608121752170809009143826, 1.2382227183354850064529787321534,
    1.2399189159605752048520550759500, 1.2416104854740858331429509912674,
    1.2432974583171476039125208457138, 1.2449798655905248647881774585442,
    1.2466577380596615040817183752122, 1.2483311061596320330678687683278,
    1.2500000000000000000000000000000, 1.2516644493695858335718170483743,
    1.2533244837411461578909044387303, 1.2549801322759665670777461332602,
    1.2566314238283697952843517179059, 1.2582783869501411671842892252039
};

#endif
/*  End of include guard.                                                     */