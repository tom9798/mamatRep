bin/bash/!#

for i in {0..3}; do
	./firewall.sh "tests/test$i-rules.in" <tests/test$i-pkts.in >tests/test$i-pkts.test
done

for i in {0..3}; do
	p=$(diff ./tests/test$i-pkts.out ./tests/test$i-pkts.test)
	if [[ -z "$p" ]]; then
		echo "passed test$i."
	fi

	if [[ -n "$p" ]]; then
		echo "failed test$i."
	fi
done