#!/bin/bash

#lineinfo pairing
##unio
##################################

./main -s inputs/SparkSoot/Soot_v32/JodaSoot32 -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/joda-time/joda-time.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/joda-time/joda-time-2.9.9.dot -j inputs/JCG_new/Joda/JodaJCG.call -w inputs/_with_lineinfo/wala_ZeroOneContainerCFA_with_lineinfo/joda-time-2.9.9/joda-time-2.9.9.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/joda-time/joda-time.dot -projectName JodaLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1

. clean JodaLineInfoUnio


./main -s inputs/SparkSoot/Soot_v32/LangSoot32 -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-lang/commons-lang.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-lang/commons-lang.dot -j inputs/JCG_new/Lang/JCGLang.call -w inputs/_with_lineinfo/wala_ZeroOneContainerCFA_with_lineinfo/commons-lang/commons-lang.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-lang/commons-lang-LANG_3_7.dot -projectName LangLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1

. clean LangLineInfoUnio


./main -s inputs/SparkSoot/Soot_v32/MathSoot32 -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-math/commons-math.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-math/commons-math.dot -j inputs/JCG_new/Math/MathJCG.call -w inputs/_with_lineinfo/wala_ZeroOneContainerCFA_with_lineinfo/commons-math/commons-math.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-math/commons-math-MATH_3_6_1.dot -projectName MathLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1

. clean MathLineInfoUnio


./main -s inputs/SparkSoot/Soot_v32/CallESoot32 -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -j inputs/JCG_new/CallEdgeExample/callEdgesExampleJCG.call -w inputs/_with_lineinfo/wala_ZeroOneContainerCFA_with_lineinfo/istvan_example/CallEdgeExample.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/istvan_example_v2/CalledgeExample.dot -projectName CallEdgeExamplesLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1

. clean CallEdgeExamplesLineInfoUnio