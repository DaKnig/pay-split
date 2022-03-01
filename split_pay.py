#!/usr/bin/env python

import time

def main():
	total = 0
	sums = {}

	log = open("pay.log", "a")
	t = time.localtime()
	print(f"-- new session {t.tm_hour}:{t.tm_min} {t.tm_mday}/{t.tm_mon}/{t.tm_year} --", file=log)
	while True:
		name = input("paid by (leave empty for end; 'list' for internal list): ")
		if name == "": # empty name means exit the loop
			break
		if name == "list":
			for name, sum in sums.items():
				print(f"{name} - {sum}")
			continue

		sum = float(input("sum paid: "))
		if name in sums.keys():
			sums[name] += sum
		else:
			sums[name] = sum

		total += sum

		print(f"{name}: {sum}", file=log) # logging

	# now the split
	avg = total / len(sums)
	print(f"\neach person shall pay {avg:.2f}\n")
	print(f"\neach person shall pay {avg:.2f}\n", file=log)

	sums = list(sums.items())
	sums = [[person[0], person[1]-avg] for person in sums] # balance
	sums = [*filter(lambda person: person[1]!=0, sums)]

	while sums != []:
		sums.sort(key = lambda item: item[1]) # sort
		# now the biggest debter pays the biggest creditor
		sum_to_pay = min(abs(sums[0][1]), abs(sums[-1][1]))

		print(f"{sums[0][0]} pays {sum_to_pay:.2f} to {sums[-1][0]}")
		print(f"{sums[0][0]} pays {sum_to_pay:.2f} to {sums[-1][0]}", file=log)

		sums[-1][1] -= sum_to_pay
		sums[0][1] += sum_to_pay

		sums = [*filter(lambda person: abs(person[1])>1e-5, sums)]

	print(f"-- session end --", file=log)

if __name__ == "__main__":
	main()
