#ifndef TMPL_MATH_RCPR_TABLE_FLOAT_H
#define TMPL_MATH_RCPR_TABLE_FLOAT_H

/*  The values 1/(1 + k/128) for k = 0, 1, ..., 126, 127.                     */
static float tmpl_float_rcpr_table[128] = {
    1.00000000000000000000000000000000F, 0.99224806201550387596899224806202F,
    0.98461538461538461538461538461538F, 0.97709923664122137404580152671756F,
    0.96969696969696969696969696969697F, 0.96240601503759398496240601503759F,
    0.95522388059701492537313432835821F, 0.94814814814814814814814814814815F,
    0.94117647058823529411764705882353F, 0.93430656934306569343065693430657F,
    0.92753623188405797101449275362319F, 0.92086330935251798561151079136691F,
    0.91428571428571428571428571428571F, 0.90780141843971631205673758865248F,
    0.90140845070422535211267605633803F, 0.89510489510489510489510489510490F,
    0.88888888888888888888888888888889F, 0.88275862068965517241379310344828F,
    0.87671232876712328767123287671233F, 0.87074829931972789115646258503401F,
    0.86486486486486486486486486486486F, 0.85906040268456375838926174496644F,
    0.85333333333333333333333333333333F, 0.84768211920529801324503311258278F,
    0.84210526315789473684210526315789F, 0.83660130718954248366013071895425F,
    0.83116883116883116883116883116883F, 0.82580645161290322580645161290323F,
    0.82051282051282051282051282051282F, 0.81528662420382165605095541401274F,
    0.81012658227848101265822784810127F, 0.80503144654088050314465408805031F,
    0.80000000000000000000000000000000F, 0.79503105590062111801242236024845F,
    0.79012345679012345679012345679012F, 0.78527607361963190184049079754601F,
    0.78048780487804878048780487804878F, 0.77575757575757575757575757575758F,
    0.77108433734939759036144578313253F, 0.76646706586826347305389221556886F,
    0.76190476190476190476190476190476F, 0.75739644970414201183431952662722F,
    0.75294117647058823529411764705882F, 0.74853801169590643274853801169591F,
    0.74418604651162790697674418604651F, 0.73988439306358381502890173410405F,
    0.73563218390804597701149425287356F, 0.73142857142857142857142857142857F,
    0.72727272727272727272727272727273F, 0.72316384180790960451977401129944F,
    0.71910112359550561797752808988764F, 0.71508379888268156424581005586592F,
    0.71111111111111111111111111111111F, 0.70718232044198895027624309392265F,
    0.70329670329670329670329670329670F, 0.69945355191256830601092896174863F,
    0.69565217391304347826086956521739F, 0.69189189189189189189189189189189F,
    0.68817204301075268817204301075269F, 0.68449197860962566844919786096257F,
    0.68085106382978723404255319148936F, 0.67724867724867724867724867724868F,
    0.67368421052631578947368421052632F, 0.67015706806282722513089005235602F,
    0.66666666666666666666666666666667F, 0.66321243523316062176165803108808F,
    0.65979381443298969072164948453608F, 0.65641025641025641025641025641026F,
    0.65306122448979591836734693877551F, 0.64974619289340101522842639593909F,
    0.64646464646464646464646464646465F, 0.64321608040201005025125628140704F,
    0.64000000000000000000000000000000F, 0.63681592039800995024875621890547F,
    0.63366336633663366336633663366337F, 0.63054187192118226600985221674877F,
    0.62745098039215686274509803921569F, 0.62439024390243902439024390243902F,
    0.62135922330097087378640776699029F, 0.61835748792270531400966183574879F,
    0.61538461538461538461538461538462F, 0.61244019138755980861244019138756F,
    0.60952380952380952380952380952381F, 0.60663507109004739336492890995261F,
    0.60377358490566037735849056603774F, 0.60093896713615023474178403755869F,
    0.59813084112149532710280373831776F, 0.59534883720930232558139534883721F,
    0.59259259259259259259259259259259F, 0.58986175115207373271889400921659F,
    0.58715596330275229357798165137615F, 0.58447488584474885844748858447489F,
    0.58181818181818181818181818181818F, 0.57918552036199095022624434389140F,
    0.57657657657657657657657657657658F, 0.57399103139013452914798206278027F,
    0.57142857142857142857142857142857F, 0.56888888888888888888888888888889F,
    0.56637168141592920353982300884956F, 0.56387665198237885462555066079295F,
    0.56140350877192982456140350877193F, 0.55895196506550218340611353711790F,
    0.55652173913043478260869565217391F, 0.55411255411255411255411255411255F,
    0.55172413793103448275862068965517F, 0.54935622317596566523605150214592F,
    0.54700854700854700854700854700855F, 0.54468085106382978723404255319149F,
    0.54237288135593220338983050847458F, 0.54008438818565400843881856540084F,
    0.53781512605042016806722689075630F, 0.53556485355648535564853556485356F,
    0.53333333333333333333333333333333F, 0.53112033195020746887966804979253F,
    0.52892561983471074380165289256198F, 0.52674897119341563786008230452675F,
    0.52459016393442622950819672131148F, 0.52244897959183673469387755102041F,
    0.52032520325203252032520325203252F, 0.51821862348178137651821862348178F,
    0.51612903225806451612903225806452F, 0.51405622489959839357429718875502F,
    0.51200000000000000000000000000000F, 0.50996015936254980079681274900398F,
    0.50793650793650793650793650793651F, 0.50592885375494071146245059288538F,
    0.50393700787401574803149606299213F, 0.50196078431372549019607843137255F
};

#endif
