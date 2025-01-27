bin/bash/!#

for i in {0..3}; do
	./firewall.sh "for-students/test$i-rules.in" <for-students/test$i-pkts.in >for-students/test$i-pkts.test
done

for i in {0..3}; do
	p=$(diff ./for-students/test$i-pkts.out ./for-students/test$i-pkts.test)
	if [[ -z "$p" ]]; then
		echo "passed test$i."
	fi

	if [[ -n "$p" ]]; then
		echo "failed test$i."
	fi
done