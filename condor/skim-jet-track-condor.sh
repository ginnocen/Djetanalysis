#!/bin/bash

if [[ $# -ne 5 ]]; then
    echo "usage: ./skim-jet-track-condor.sh [input list] [output dir] [residuals] [isPP] [jetptmin]"
    exit 1
fi

g++ ../skim/jet_track_skim.C -o jet_track_skim.exe $(root-config --cflags --libs) -Werror -Wall -O2 || exit 1

mkdir -p $2

JOBS=$(cat $1 | wc -l)

cat > skim-jet-track.condor <<EOF
Universe     = vanilla
Initialdir   = $PWD/
Notification = Error
Executable   = $PWD/skim-jet-track.sh
Arguments    = \$(Process) $1 $2 $3 $4 $5
GetEnv       = True
Output       = $PWD/logs/\$(Process).out
Error        = $PWD/logs/\$(Process).err
Log          = $PWD/logs/\$(Process).log
Rank         = Mips
+AccountingGroup = "group_cmshi.$(whoami)"
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = jet_track_skim.exe,$3,$1
#noop_job = !( stringListMember("\$(Process)","") )

Queue $JOBS
EOF

cat > skim-jet-track.sh <<EOF
tar -xzvf \$4

FILE=\$(head -n\$((\$1+1)) \$2 | tail -n1)

if [[ \$5 -eq 1 ]]; then
    JETALGO=ak3PFJetAnalyzer
    MIXINGFILE='""'
else
    JETALGO=akPu3PFJetAnalyzer
    MIXINGFILE=/mnt/hadoop/cms/store/user/rbi/merged/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1/0.root
fi

echo ./jet_track_skim.exe \$FILE \${1}.root \$JETALGO \$5 1 \$MIXINGFILE \$6
./jet_track_skim.exe \$FILE \${1}.root \$JETALGO \$5 1 \$MIXINGFILE \$6

if [[ \$? -eq 0 ]]; then
    mv \${1}.root \${3}
fi

rm -f *.root
EOF

condor_submit skim-jet-track.condor
