#!/bin/bash

./main -s bemenetek/soot/Java_samples/dot/2_class/Anonym/soot-Anonym3RefForward -sm bemenetek/SM/java_samples/Anonym3RefForward.dot -sp bemenetek/spoon/java_samples/Anonym3RefForward.dot -c bemenetek/CHP/zoli_anonym_chp/Anonym_Ref_Forward.txt -g bemenetek/gousiosg/zoli_anonymous_gousiosg/Anonym_Ref_Forward.txt -w bemenetek/wala/Anonym3/Anonym3.dot -projectName Anonym3 -CHPtransformation 1 -anonymTransformation 1

mkdir Anonym3
mv *.txt Anonym3
mv *.tsv Anonym3
mv *.list Anonym3

./main -s bemenetek/soot/Istvan/commons-Istvan-peldak-soot-MainClass -sm bemenetek/SM/istvan_example/CallEdgeExamples.dot -sp bemenetek/spoon/istvan_example/v3/CallEdgeExamples.dot -c bemenetek/CHP/Istvan/Istvan_CHP.txt -g bemenetek/gousiosg/Istvan/Istvan_GOUSIOSG.txt -w bemenetek/wala/istvan_example_vStorage/CallEdgeExamples.DOT -projectName IstvanExample -CHPtransformation 1 -anonymTransformation 1

mkdir Istvan
mv *.txt Istvan
mv *.tsv Istvan
mv *.list Istvan