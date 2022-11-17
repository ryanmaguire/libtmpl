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
#include <libtmpl/include/tmpl_math.h>

/*  Table of the values log(1 + k/128) for k = 0, 1, ..., 126, 127.           */
const float tmpl_float_log_table[128] = {
    0.00000000000000000000000000000000000000F,
    0.00778214044205494894746290006113676368F,
    0.0155041865359652541508540460424468359F,
    0.0231670592815343782287991609622899166F,
    0.0307716586667536883710282075967721641F,
    0.0383188643021365991937553251237972903F,
    0.0458095360312942031666792676146633421F,
    0.0532445145188122828658701937865287769F,
    0.0606246218164348425806061320404202633F,
    0.0679506619085077493945652777726294140F,
    0.0752234212375875256986053399836624146F,
    0.0824436692110745912681600686683078059F,
    0.0896121586896871326199514693784845288F,
    0.0967296264585511122955710564874634370F,
    0.103796793681643564826061803763974688F,
    0.110814366340290114194806169323211928F,
    0.117783035656383454538794109470521705F,
    0.124703478500957235863406515380863268F,
    0.131576357788719272588716128689483162F,
    0.138402322859119135685325873601649187F,
    0.145182009844497897281935063740564324F,
    0.151916042025841975071803424896884511F,
    0.158605030176638584093371174625841575F,
    0.165249572895307162875611449277240314F,
    0.171850256926659222340098946055147265F,
    0.178407657472818297119400241510941968F,
    0.184922338494011992663903592659249621F,
    0.191394852999629454609298807561308873F,
    0.197825743329919880362572071196961469F,
    0.204215541428690891503820386196239272F,
    0.210564769107349637669552812732351514F,
    0.216873938300614359619089525744347498F,
    0.223143551314209755766295090309834503F,
    0.229374101064845829991480725046139872F,
    0.235566071312766909077588218941043410F,
    0.241719936887145168144307515913513900F,
    0.247836163904581256780602765746524748F,
    0.253915209980963444137323297906606667F,
    0.259957524436926066972079494542311045F,
    0.265963548497137941339125926537543389F,
    0.271933715483641758831669494532999162F,
    0.277868451003456306186350032923401233F,
    0.283768173130644598346901222350254767F,
    0.289633292583042676878893055525668970F,
    0.295464212893835876386681906054964195F,
    0.301261330578161781012875538233755493F,
    0.307025035294911862075124540535377902F,
    0.312755710003896888386246559688319032F,
    0.318453731118534615810247213590599596F,
    0.324119468654211976090670760434987352F,
    0.329753286372467981814422811920789811F,
    0.335355541921137830257179579814166199F,
    0.340926586970593210305089199780356208F,
    0.346466767346208580918462188425772951F,
    0.351976423157178184655447456259438926F,
    0.357455888921803774226009490140904474F,
    0.362905493689368453137824345977489846F,
    0.368325561158707653048230154050398827F,
    0.373716409793584080821016832715823507F,
    0.379078352934969458390853345631019859F,
    0.384411698910332039734790062481290869F,
    0.389716751140025213370463604003520867F,
    0.394993808240868978106394036364981768F,
    0.400243164127012706929325101995131170F,
    0.405465108108164381978013115464349137F,
    0.410659924985268385934306203175822788F,
    0.415827895143710965613328892954902305F,
    0.420969294644129636128867161506795972F,
    0.426084395310900063124544879595476619F,
    0.431173464818371340859172478955594998F,
    0.436236766774918070349041323061121301F,
    0.441274560804875229489496441661301225F,
    0.446287102628419511532590180619669007F,
    0.451274644139458585144692383079012479F,
    0.456237433481587594380805538163929748F,
    0.461175715122170166367999925597855359F,
    0.466089729924599224558619247504769400F,
    0.470979715218791012546897856056359251F,
    0.475845904869963914265209586304381412F,
    0.480688529345751907676618455448011551F,
    0.485507815781700807801791077190788901F,
    0.490303988045193838150346159645746861F,
    0.495077266797851514597964584842833665F,
    0.499827869556449329821331415247044142F,
    0.504556010752395287058308531738174930F,
    0.509261901789807946804074919228323825F,
    0.513945751102234316801006088274217593F,
    0.518607764208045632152976996364798699F,
    0.523248143764547836516807224934870842F,
    0.527867089620842385113892217778300964F,
    0.532464798869471843873923723460142243F,
    0.537041465896883654566729244153832299F,
    0.541597282432744371576542303900434099F,
    0.546132437598135650382397209231209164F,
    0.550647117952662279259948179204913460F,
    0.555141507540501592715480359515904050F,
    0.559615787935422686270888500526826593F,
    0.564070138284802966071384290090190712F,
    0.568504735352668712078738764866962264F,
    0.572919753561785509092756726626261069F,
    0.577315365034823604318112061519496402F,
    0.581691739634622482520610753725372341F,
    0.586049045003578208904119436287324350F,
    0.590387446602176374641916708123598758F,
    0.594707107746692789514343546529205333F,
    0.599008189646083399381600024461651502F,
    0.603290851438084262340585186661310606F,
    0.607555250224541795501085152791125372F,
    0.611801541105992903529889766428814784F,
    0.616029877215514019647565928196700650F,
    0.620240409751857528851494632567246857F,
    0.624433288011893501042538744054673120F,
    0.628608659422374137744308205774183640F,
    0.632766669571037829545786468503579758F,
    0.636907462237069231620494427181199191F,
    0.641031179420931291055601334405392547F,
    0.645137961373584701665228496134731906F,
    0.649227946625109818890839969905311122F,
    0.653301272012745638758615881210873885F,
    0.657358072708360030141890023245936166F,
    0.661398482245365008260235838709650938F,
    0.665422632545090448950092610006660181F,
    0.669430653942629267298885270929503510F,
    0.673422675212166720297960388801017265F,
    0.677398823591806140809682609997348299F,
    0.681359224807903068948071559568089442F,
    0.685304003098919416544048078967232986F,
    0.689233281238808980324914337814603903F
};