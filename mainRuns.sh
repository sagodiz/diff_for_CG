#!/bin/bash

#lineinfo and generic pairing
##unio
##################################

./main -s inputs/SparkSoot/Soot_v32_latest/JodaLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/joda-time/joda-time.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/joda-time/joda-time-2.9.9.dot -j inputs/JCG_new/Joda/JodaJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/joda-time.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/joda-time/joda-time.dot -projectName JodaLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1

. clean JodaLineInfoUnio


./main -s inputs/SparkSoot/Soot_v32_latest/LangLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-lang/commons-lang.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-lang/commons-lang.dot -j inputs/JCG_new/Lang/JCGLang.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/commons-lang.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-lang/commons-lang-LANG_3_7.dot -projectName LangLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1

. clean LangLineInfoUnio


./main -s inputs/SparkSoot/Soot_v32_latest/MathLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-math/commons-math.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-math/commons-math.dot -j inputs/JCG_new/Math/MathJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/commons-math.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-math/commons-math-MATH_3_6_1.dot -projectName MathLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1

. clean MathLineInfoUnio


./main -s inputs/SparkSoot/Soot_v32_latest/CallEFullSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -j inputs/JCG_new/CallEdgeExample/callEdgesExampleJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/CallEdgeExample.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/istvan_example_v2/CalledgeExample.dot -projectName CallEdgeExamplesLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1

. clean CallEdgeExamplesLineInfoUnio


./main -s inputs/SparkSoot/Soot_v32_latest/argoFullSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/argouml/argouml.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/argouml/argouml.dot -j inputs/JCG_new/ArgoUML/argoFullJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/argouml.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/argouml/argouml.dot -projectName ArgoLineInfo -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1

. clean ArgoLineInfoUnio


###only anonym pairing with lineinfo

./main -s inputs/SparkSoot/Soot_v32_latest/JodaLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/joda-time/joda-time.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/joda-time/joda-time-2.9.9.dot -j inputs/JCG_new/Joda/JodaJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/joda-time.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/joda-time/joda-time.dot -projectName JodaLineInfoOnlyAnonym -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1 -onlyAnonym 

. clean JodaLineInfoUnioOnlyAnonym


./main -s inputs/SparkSoot/Soot_v32_latest/LangLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-lang/commons-lang.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-lang/commons-lang.dot -j inputs/JCG_new/Lang/JCGLang.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/commons-lang.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-lang/commons-lang-LANG_3_7.dot -projectName LangLineInfoOnlyAnonym -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1 -onlyAnonym 

. clean LangLineInfoUnioOnlyAnonym


./main -s inputs/SparkSoot/Soot_v32_latest/MathLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-math/commons-math.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-math/commons-math.dot -j inputs/JCG_new/Math/MathJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/commons-math.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-math/commons-math-MATH_3_6_1.dot -projectName MathLineInfoOnlyAnonym -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1 -onlyAnonym 

. clean MathLineInfoUnioOnlyAnonym


./main -s inputs/SparkSoot/Soot_v32_latest/CallEFullSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -j inputs/JCG_new/CallEdgeExample/callEdgesExampleJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/CallEdgeExample.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/istvan_example_v2/CalledgeExample.dot -projectName CallEdgeExamplesLineInfoOnlyAnonym -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1 -onlyAnonym

. clean CallEdgeExamplesLineInfoUnioOnlyAnonym


./main -s inputs/SparkSoot/Soot_v32_latest/argoFullSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/argouml/argouml.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/argouml/argouml.dot -j inputs/JCG_new/ArgoUML/argoFullJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/argouml.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/argouml/argouml.dot -projectName ArgoLineInfoOnlyAnonym -methodUnio 0 -lineInfoPairing 1 -calcUnionGraph 1 -genericParameterTypeNames 1 -onlyAnonym

. clean ArgoLineInfoUnioOnlyAnonym

##### anonym transformation pairing
#############################################################

./main -s inputs/SparkSoot/Soot_v32_latest/JodaLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/joda-time/joda-time.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/joda-time/joda-time-2.9.9.dot -j inputs/JCG_new/Joda/JodaJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/joda-time.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/joda-time/joda-time.dot -projectName JodaAnonymTransformation -methodUnio 0 -calcUnionGraph 1 -genericParameterTypeNames 1 -anonymTransformation 1

. clean JodaAnonymTransformation


./main -s inputs/SparkSoot/Soot_v32_latest/LangLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-lang/commons-lang.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-lang/commons-lang.dot -j inputs/JCG_new/Lang/JCGLang.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/commons-lang.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-lang/commons-lang-LANG_3_7.dot -projectName LangAnonymTransformation -methodUnio 0 -calcUnionGraph 1 -genericParameterTypeNames 1 -anonymTransformation 1

. clean LangAnonymTransformation


./main -s inputs/SparkSoot/Soot_v32_latest/MathLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-math/commons-math.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-math/commons-math.dot -j inputs/JCG_new/Math/MathJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/commons-math.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-math/commons-math-MATH_3_6_1.dot -projectName MathAnonymTransformation -methodUnio 0 -calcUnionGraph 1 -genericParameterTypeNames 1 -anonymTransformation 1

. clean MathAnonymTransformation


./main -s inputs/SparkSoot/Soot_v32_latest/CallEFullSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -j inputs/JCG_new/CallEdgeExample/callEdgesExampleJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/CallEdgeExample.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/istvan_example_v2/CalledgeExample.dot -projectName CallEdgeExamplesAnonymTransformation -methodUnio 0 -calcUnionGraph 1 -genericParameterTypeNames 1 -anonymTransformation 1

. clean CallEdgeExamplesAnonymTransformation


./main -s inputs/SparkSoot/Soot_v32_latest/argoFullSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/argouml/argouml.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/argouml/argouml.dot -j inputs/JCG_new/ArgoUML/argoFullJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/argouml.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/argouml/argouml.dot -projectName ArgoAnonymTransformation -methodUnio 0 -calcUnionGraph 1 -genericParameterTypeNames 1 -anonymTransformation 1

. clean ArgoAnonymTransformation

############basic name pairing#########
################################################################

./main -s inputs/SparkSoot/Soot_v32_latest/JodaLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/joda-time/joda-time.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/joda-time/joda-time-2.9.9.dot -j inputs/JCG_new/Joda/JodaJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/joda-time.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/joda-time/joda-time.dot -projectName JodaNamePairing -calcUnionGraph 1 -genericParameterTypeNames 1

. clean JodaNamePairing


./main -s inputs/SparkSoot/Soot_v32_latest/LangLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-lang/commons-lang.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-lang/commons-lang.dot -j inputs/JCG_new/Lang/JCGLang.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/commons-lang.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-lang/commons-lang-LANG_3_7.dot -projectName LangNamePairing -calcUnionGraph 1 -genericParameterTypeNames 1

. clean LangNamePairing


./main -s inputs/SparkSoot/Soot_v32_latest/MathLibSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/commons-math/commons-math.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/commons-math/commons-math.dot -j inputs/JCG_new/Math/MathJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/commons-math.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/commons-math/commons-math-MATH_3_6_1.dot -projectName MathNamePairing -calcUnionGraph 1 -genericParameterTypeNames 1

. clean MathNamePairing


./main -s inputs/SparkSoot/Soot_v32_latest/CallEFullSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/istvan_example_v2/CallEdgeExamples.dot -j inputs/JCG_new/CallEdgeExample/callEdgesExampleJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/CallEdgeExample.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/istvan_example_v2/CalledgeExample.dot -projectName CallEdgeExamplesNamePairing -calcUnionGraph 1 -genericParameterTypeNames 1

. clean CallEdgeExamplesNamePairing


./main -s inputs/SparkSoot/Soot_v32_latest/argoFullSootDirectory.dot -osa inputs/_with_lineinfo/SourceMeter_with_lineinfo/argouml/argouml.dot -sp inputs/_with_lineinfo/spoon_with_lineinfo/argouml/argouml.dot -j inputs/JCG_new/ArgoUML/argoFullJCG.call -w inputs/_with_lineinfo/new_wala_ZeroOneContainerCFA_with_lineinfo/argouml.dot -jdt inputs/_with_lineinfo/jdt_with_lineinfo/argouml/argouml.dot -projectName ArgoNamePairing -calcUnionGraph 1 -genericParameterTypeNames 1

. clean ArgoNamePairing

