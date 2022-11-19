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
#ifndef TMPL_MATH_SIND_LOOKUP_TABLE_DOUBLE_H
#define TMPL_MATH_SIND_LOOKUP_TABLE_DOUBLE_H

/*  The values sin((pi/180)*k) for k = 0, 1, ..., 179.                        */
static const double tmpl_Double_Sind_Lookup_Table[180] = {
    0.000000000000000000000000000000000000000000,
    0.017452406437283512819418978516316192472253,
    0.034899496702500971645995181625332937354825,
    0.052335956242943832722118629609078418731018,
    0.069756473744125300775958835194143328600903,
    0.087155742747658173558064270837473551377701,
    0.10452846326765347139983415480249811908066,
    0.12186934340514748111289391923152517601324,
    0.13917310096006544411249666330110527545592,
    0.15643446504023086901010531946716689231390,
    0.17364817766693034885171662676931479600038,
    0.19080899537654481240514048795838761962792,
    0.20791169081775933710174228440512516621658,
    0.22495105434386499805110720834279655863101,
    0.24192189559966772256044237410035296529501,
    0.25881904510252076234889883762404832834907,
    0.27563735581699918564997157461130414771245,
    0.29237170472273672809746869537714325266469,
    0.30901699437494742410229341718281905886015,
    0.32556815445715666871400893579472157179885,
    0.34202014332566873304409961468225958076308,
    0.35836794954530027348413778941346683419154,
    0.37460659341591203541496377450119513100016,
    0.39073112848927375506208458888909426761802,
    0.40673664307580020775398599034149761292314,
    0.42261826174069943618697848964773018156313,
    0.43837114678907741745273454065826573906276,
    0.45399049973954679156040836635787119898305,
    0.46947156278589077595946228822784329572322,
    0.48480962024633702907537962241577656827666,
    0.50000000000000000000000000000000000000000,
    0.51503807491005421008163193639813828341608,
    0.52991926423320495404678115181608666877202,
    0.54463903501502708222408369208156538160790,
    0.55919290347074683016042813998598928730662,
    0.57357643635104609610803191282615786462043,
    0.58778525229247312916870595463907276859765,
    0.60181502315204827991797700044148984142564,
    0.61566147532565827966881109284365562825093,
    0.62932039104983745270590245827997042656686,
    0.64278760968653932632264340990726343290756,
    0.65605902899050728478249596402341924751940,
    0.66913060635885821382627333068678047359958,
    0.68199836006249850044222578471112558034043,
    0.69465837045899728665640629942268622991981,
    0.70710678118654752440084436210484903928484,
    0.71933980033865113935605467445671190823068,
    0.73135370161917048328754360827562240337840,
    0.74314482547739423501469704897425697718911,
    0.75470958022277199794298421956101555804854,
    0.76604444311897803520239265055541667393583,
    0.77714596145697087997993774367240384909207,
    0.78801075360672195669397778783585166664170,
    0.79863551004729284628400080406893624426627,
    0.80901699437494742410229341718281905886015,
    0.81915204428899178968448838591684343189001,
    0.82903757255504169200633684150164202632907,
    0.83867056794542402963759094180454789403950,
    0.84804809615642597038617617869038644872871,
    0.85716730070211228746521798014476331438405,
    0.86602540378443864676372317075293618347140,
    0.87461970713939580028463695866107950685631,
    0.88294759285892694203217136031571938608354,
    0.89100652418836786235970957141362631277052,
    0.89879404629916699278229567669578535492997,
    0.90630778703664996324255265675431698326771,
    0.91354545764260089550212757198531717794081,
    0.92050485345244032739689472330046142027950,
    0.92718385456678740080647445113695694209762,
    0.93358042649720174899004306313957074140597,
    0.93969262078590838405410927732473146993621,
    0.94551857559931681034812470751940317767646,
    0.95105651629515357211643933337938214340570,
    0.95630475596303548133865081661841896200941,
    0.96126169593831886191649704855706487352569,
    0.96592582628906828674974319972889736763390,
    0.97029572627599647230637787403399037763226,
    0.97437006478523522853969448008826883300512,
    0.97814760073380563792856674786959953245974,
    0.98162718344766395349650489981814081931825,
    0.98480775301220805936674302458952301367064,
    0.98768834059513772619004024769343726075841,
    0.99026806874157031508377486734485075925109,
    0.99254615164132203498006158933058410904365,
    0.99452189536827333692269194498057038152079,
    0.99619469809174553229501040247388804618356,
    0.99756405025982424761316268064425502636938,
    0.99862953475457387378449205843943658059095,
    0.99939082701909573000624344004392996449524,
    0.99984769515639123915701155881391485169274,
    1.0000000000000000000000000000000000000000,
    0.99984769515639123915701155881391485169274,
    0.99939082701909573000624344004392996449524,
    0.99862953475457387378449205843943658059095,
    0.99756405025982424761316268064425502636938,
    0.99619469809174553229501040247388804618356,
    0.99452189536827333692269194498057038152079,
    0.99254615164132203498006158933058410904365,
    0.99026806874157031508377486734485075925109,
    0.98768834059513772619004024769343726075841,
    0.98480775301220805936674302458952301367064,
    0.98162718344766395349650489981814081931825,
    0.97814760073380563792856674786959953245974,
    0.97437006478523522853969448008826883300512,
    0.97029572627599647230637787403399037763226,
    0.96592582628906828674974319972889736763390,
    0.96126169593831886191649704855706487352569,
    0.95630475596303548133865081661841896200941,
    0.95105651629515357211643933337938214340570,
    0.94551857559931681034812470751940317767646,
    0.93969262078590838405410927732473146993621,
    0.93358042649720174899004306313957074140597,
    0.92718385456678740080647445113695694209762,
    0.92050485345244032739689472330046142027950,
    0.91354545764260089550212757198531717794081,
    0.90630778703664996324255265675431698326771,
    0.89879404629916699278229567669578535492997,
    0.89100652418836786235970957141362631277052,
    0.88294759285892694203217136031571938608354,
    0.87461970713939580028463695866107950685631,
    0.86602540378443864676372317075293618347140,
    0.85716730070211228746521798014476331438405,
    0.84804809615642597038617617869038644872871,
    0.83867056794542402963759094180454789403950,
    0.82903757255504169200633684150164202632907,
    0.81915204428899178968448838591684343189001,
    0.80901699437494742410229341718281905886015,
    0.79863551004729284628400080406893624426627,
    0.78801075360672195669397778783585166664170,
    0.77714596145697087997993774367240384909207,
    0.76604444311897803520239265055541667393583,
    0.75470958022277199794298421956101555804854,
    0.74314482547739423501469704897425697718911,
    0.73135370161917048328754360827562240337840,
    0.71933980033865113935605467445671190823068,
    0.70710678118654752440084436210484903928484,
    0.69465837045899728665640629942268622991981,
    0.68199836006249850044222578471112558034043,
    0.66913060635885821382627333068678047359958,
    0.65605902899050728478249596402341924751940,
    0.64278760968653932632264340990726343290756,
    0.62932039104983745270590245827997042656686,
    0.61566147532565827966881109284365562825093,
    0.60181502315204827991797700044148984142564,
    0.58778525229247312916870595463907276859765,
    0.57357643635104609610803191282615786462043,
    0.55919290347074683016042813998598928730662,
    0.54463903501502708222408369208156538160790,
    0.52991926423320495404678115181608666877202,
    0.51503807491005421008163193639813828341608,
    0.50000000000000000000000000000000000000000,
    0.48480962024633702907537962241577656827666,
    0.46947156278589077595946228822784329572322,
    0.45399049973954679156040836635787119898305,
    0.43837114678907741745273454065826573906276,
    0.42261826174069943618697848964773018156313,
    0.40673664307580020775398599034149761292314,
    0.39073112848927375506208458888909426761802,
    0.37460659341591203541496377450119513100016,
    0.35836794954530027348413778941346683419154,
    0.34202014332566873304409961468225958076308,
    0.32556815445715666871400893579472157179885,
    0.30901699437494742410229341718281905886015,
    0.29237170472273672809746869537714325266469,
    0.27563735581699918564997157461130414771245,
    0.25881904510252076234889883762404832834907,
    0.24192189559966772256044237410035296529501,
    0.22495105434386499805110720834279655863101,
    0.20791169081775933710174228440512516621658,
    0.19080899537654481240514048795838761962792,
    0.17364817766693034885171662676931479600038,
    0.15643446504023086901010531946716689231390,
    0.13917310096006544411249666330110527545592,
    0.12186934340514748111289391923152517601324,
    0.10452846326765347139983415480249811908066,
    0.087155742747658173558064270837473551377701,
    0.069756473744125300775958835194143328600903,
    0.052335956242943832722118629609078418731018,
    0.034899496702500971645995181625332937354825,
    0.017452406437283512819418978516316192472253
};

#endif
/*  End of include guard.                                                     */
