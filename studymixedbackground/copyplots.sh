#!/bin/bash

INPUTFILE="test_fullstatistics20files"
NOTESPATH="/home/mjpeters/Documents/DPhiAN/notes/AN-17-097/trunk/plots/"
PLOTSPATH="/home/mjpeters/submit/CMSSW_7_5_8_patch3/src/Djetanalysis/studymixedbackground/plots/"
FOLDERS=("${INPUTFILE}signal" "mixjet_${INPUTFILE}" "mixD_${INPUTFILE}" "mixboth_${INPUTFILE}")
NAMES=("signal" "mixjet" "mixD" "mixboth")

cd $NOTESPATH

if [[ ! -d plotevtmix ]]
then
	mkdir -p plotevtmix
fi

ITER=0
cd ${PLOTSPATH}
for i in ${FOLDERS[@]}
do
	cd $i
	cp -a hJetPt.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}JetPt.pdf
	cp -a hJetEta.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}JetEta.pdf
	cp -a hJetPhi.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}JetPhi.pdf
	cp -a hDPt.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DPt.pdf
	cp -a hDEta_pt_0.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DEta_pt_0.pdf
	cp -a hDEta_pt_1.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DEta_pt_1.pdf
	cp -a hDPhi_pt_0.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DPhi_pt_0.pdf
	cp -a hDPhi_pt_1.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DPhi_pt_1.pdf
	cp -a hDdelPhi_pt_0.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DeltaPhi_pt_0.pdf
	cp -a hDdelPhi_pt_1.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DeltaPhi_pt_1.pdf
	cp -a hNumREfficiency_pt_0.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DeltaR_pt_0.pdf
	cp -a hNumREfficiency_pt_1.pdf ${NOTESPATH}/plotevtmix/${NAMES[$ITER]}DeltaR_pt_1.pdf
	(( ITER++ ))
	cd ..
done

cp -a MBsub_dphi_pt_0.pdf ${NOTESPATH}/plotevtmix/DeltaPhicompare_pt_0.pdf
cp -a MBsub_dphi_pt_1.pdf ${NOTESPATH}/plotevtmix/DeltaPhicompare_pt_1.pdf
cp -a MBsub_dr_pt_0.pdf ${NOTESPATH}/plotevtmix/DeltaRcompare_pt_0.pdf
cp -a MBsub_dr_pt_1.pdf ${NOTESPATH}/plotevtmix/DeltaRcompare_pt_1.pdf
cp -a bkgd_ratio_dr_pt_0.pdf ${NOTESPATH}/plotevtmix/BkgdRatio_dr_pt_0.pdf
cp -a bkgd_ratio_dr_pt_1.pdf ${NOTESPATH}/plotevtmix/BkgdRatio_dr_pt_1.pdf
cp -a bkgd_ratio_dphi_pt_0.pdf ${NOTESPATH}/plotevtmix/BkgdRatio_dphi_pt_0.pdf
cp -a bkgd_ratio_dphi_pt_1.pdf ${NOTESPATH}/plotevtmix/BkgdRatio_dphi_pt_1.pdf

cd ..
