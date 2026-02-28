# =========================
# MYSH TESTER (FINAL VERSION)
# =========================

PASS = "\033[32m[PASS]\033[0m"
FAIL = "\033[31m[FAIL]\033[0m"

test: myshell
	@echo "Running myshell tests..."
	@echo ""

	@# ---------- BASIC COMMANDS ----------
	@echo "echo hello" | ./myshell | grep -q "hello" \
		&& echo $(PASS) "basic echo command" \
		|| echo $(FAIL) "basic echo command"

	@echo "pwd" | ./myshell | grep -q "/" \
		&& echo $(PASS) "pwd prints path" \
		|| echo $(FAIL) "pwd prints path"

	@# ---------- OUTPUT REDIRECTION ----------
	@echo "echo redirectiontest > /tmp/mysh_test.txt" | ./myshell ; \
		grep -q "redirectiontest" /tmp/mysh_test.txt \
		&& echo $(PASS) "output redirection >" \
		|| echo $(FAIL) "output redirection >"

	@# ---------- APPEND REDIRECTION ----------
	@echo "echo appended >> /tmp/mysh_test.txt" | ./myshell ; \
		grep -q "appended" /tmp/mysh_test.txt \
		&& echo $(PASS) "append redirection >>" \
		|| echo $(FAIL) "append redirection >>"

	@# ---------- INPUT REDIRECTION ----------
	@echo "wc -l < /tmp/mysh_test.txt" | ./myshell | grep -E "[0-9]+" \
		&& echo $(PASS) "input redirection <" \
		|| echo $(FAIL) "input redirection <"

	@# ---------- BUILT-IN CD ----------
	@printf "cd /tmp\npwd\n" | ./myshell | grep -q "/tmp" \
		&& echo $(PASS) "cd changes directory" \
		|| echo $(FAIL) "cd changes directory"

	@# ---------- INVALID COMMAND ----------
	@echo "nonexistent_cmd_xyz" | ./myshell \
		&& echo $(PASS) "invalid command handled safely" \
		|| echo $(FAIL) "invalid command handled safely"

	@# ---------- EMPTY INPUT ----------
	@printf "\n\n" | ./myshell \
		&& echo $(PASS) "empty input handled" \
		|| echo $(FAIL) "empty input handled"

	@# ---------- BACKGROUND JOB ----------
	@echo "sleep 1 &" | ./myshell | grep -q "PID" \
		&& echo $(PASS) "background job prints PID" \
		|| echo $(FAIL) "background job prints PID"

	@# ---------- BACKGROUND RESPONSIVENESS (IMPORTANT) ----------
	@printf "sleep 1 &\necho done\n" | ./myshell | grep -q "done" \
		&& echo $(PASS) "shell remains responsive after background job" \
		|| echo $(FAIL) "shell blocked by background job"

	@# ---------- FILE DESCRIPTOR SAFETY ----------
	@printf "echo hi > /tmp/testfd.txt\necho visible\n" | ./myshell | grep -q "visible" \
		&& echo $(PASS) "parent shell file descriptor unchanged" \
		|| echo $(FAIL) "parent shell output broken"

	@# ---------- LONG COMMAND ----------
	@echo "echo aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" | ./myshell | grep -q "aaa" \
		&& echo $(PASS) "long command handled" \
		|| echo $(FAIL) "long command handled"

	@# ---------- MANY ARGUMENTS ----------
	@echo "echo a b c d e f g h i j k l m n o p q r s t u v w x y z" | ./myshell | grep -q "z" \
		&& echo $(PASS) "many arguments handled" \
		|| echo $(FAIL) "many arguments handled"

	@# ---------- /dev/null REDIRECTION ----------
	@echo "ls > /dev/null" | ./myshell \
		&& echo $(PASS) "redirection to /dev/null" \
		|| echo $(FAIL) "redirection to /dev/null"

	@# ---------- SPACE HANDLING ----------
	@echo "echo spacetest > /tmp/mysh_space.txt" | ./myshell ; \
		grep -q "spacetest" /tmp/mysh_space.txt \
		&& echo $(PASS) "spaces around redirection operators" \
		|| echo $(FAIL) "spaces around redirection operators"

	@rm -f /tmp/mysh_test.txt /tmp/mysh_space.txt /tmp/testfd.txt

	@echo ""
	@echo "All tests finished."
