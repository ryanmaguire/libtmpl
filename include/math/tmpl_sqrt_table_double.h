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
#ifndef TMPL_SQRT_TABLE_DOUBLE_H
#define TMPL_SQRT_TABLE_DOUBLE_H

/*  The values sqrt(1 + k/128) for k = 0, 1, ..., 126, 127.                   */
static const double tmpl_double_sqrt_table[128] = {
    1.0000000000000000000000000000000, 1.0038986502630631587814157208459,
    1.0077822185373187065458266537880, 1.0116508785149153420370293943119,
    1.0155048005794950450574854460333, 1.0193441518937556547578604929810,
    1.0231690964840562462442129655917, 1.0269797953221864627318183427515,
    1.0307764064044151374553524639935, 1.0345590848279280370779360753360,
    1.0383279828647593565730328431134, 1.0420832500333166759944035177135,
    1.0458250331675944349727150322315, 1.0495534764841665751224584232305,
    1.0532687216470448288292674882753, 1.0569709078304851811357823701735,
    1.0606601717798212866012665431573, 1.0643366478704000728833326139923,
    1.0680004681646913959839560407800, 1.0716517624676404179613117826838,
    1.0752906583803283464661841918812, 1.0789172813520042973878796249536,
    1.0825317547305483084546539634412, 1.0861341998114229346449263315813,
    1.0897247358851683880592454959649, 1.0933034802834938382889036645398,
    1.0968705484240152575507985384270, 1.1004260538536880716105767610310,
    1.1039701082909808568455053408699, 1.1075028216668344001244453185960,
    1.1110243021644486062614302094261, 1.1145346562579379927031483855089,
    1.1180339887498948482045868343656, 1.1215224028078975471714659308581,
    1.1250000000000000000000000000000, 1.1284668803292367782613181982975,
    1.1319231422671770783217260208730, 1.1353688827865593745334498036443,
    1.1388041973930373602432032630861, 1.1422291801560665785020669945915,
    1.1456439237389600016470117984320, 1.1490485194281397271513720884204,
    1.1524430571616109137502842852203, 1.1558276255566830844219110715227,
    1.1592023119369629690645520092488, 1.1625672023586421474977133451070,
    1.1659223816361018806943094427901, 1.1692679333668566829949214788489,
    1.1726039399558573886414075283861, 1.1759304826391737005723170719273,
    1.1792476415070754764150825472028, 1.1825554955265313044453633803626,
    1.1858541225631422494995850791623, 1.1891435994025280040371184834364,
    1.1924240017711820614407769825290, 1.1956954043568119359739067970636,
    1.1989578808281798853993595160407, 1.2022115038544590469909601825758,
    1.2054563451241193744700038809291, 1.2086924753633572612702712080185,
    1.2119199643540822535186101438557, 1.2151388809514737933061188942665,
    1.2183492931011204883548016499875, 1.2215512678557539772367511819066,
    1.2247448713915890490986420373529, 1.2279301690242812826432845870217,
    1.2311072252245130902182764268647, 1.2342761036332186885899038152327,
    1.2374368670764581677014776336835, 1.2405895775799504918231541078932,
    1.2437342963832749434180997762515, 1.2468710839537502082283676396337,
    1.2500000000000000000000000000000, 1.2531211034852138344224211564032,
    1.2562344526401112837774081140949, 1.2593401049756177760254071743209,
    1.2624381172952597441704232396337, 1.2655285457072866833279313931188,
    1.2686114456365274335810650148670, 1.2716868718359877760746043112424,
    1.2747548783981962075070560272557, 1.2778155187663045438976964067523,
    1.2808688457449497979026298350651, 1.2839149115108835747211747948459,
    1.2869537676233750394746711830247, 1.2899854650343933235708268617173,
    1.2930100540985750587173249303284, 1.2960275845829825546599366749906,
    1.2990381056766579701455847561294, 1.3020416659999786658132951021649,
    1.3050383136138187724697192528185, 1.3080280960285218582946961804402,
    1.3110110602126894337393168920999, 1.3139872526017898930262410660935,
    1.3169567191065923560501755827375, 1.3199195051214297439241398350616,
    1.3228756555322952952508078768196, 1.3258252147247766082515831789466,
    1.3287682265918311759998902393662, 1.3317047345414072680269071455173,
    1.3346347815039139013514404956995, 1.3375584099395435373907689818678,
    1.3404756618454510381017699590193, 1.3433865787627923149527506609676,
    1.3462912017836260078126776228851, 1.3491895715576814374475295341304,
    1.3520817282989959849197079753014, 1.3549677117924249636868515300458,
    1.3578475614000269654864366718422, 1.3607213160673275790718439061685,
    1.3635890143294643014377693109216, 1.3664506943172153842454612562837,
    1.3693063937629152836424244570020, 1.3721561500062593094816361902560,
    1.3750000000000000000000000000000, 1.3778379803155376802359722920221,
    1.3806701271484075967763642304180, 1.3834964763236659577495159256893,
    1.3863170633011771452564500128262, 1.3891319231808043075860224840425,
    1.3919410907075054805298678247296, 1.3947446002763373308359242543712,
    1.3975424859373685602557335429570, 1.4003347814005049556930185898401,
    1.4031215200402280195939057746187, 1.4059027349002490648793174696195,
    1.4086784586980806103562504614679, 1.4114487238295268656075312412307
};

#endif
/*  End of include guard.                                                     */
