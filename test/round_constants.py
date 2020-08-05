last = 1
for i in range(2, 11):
    if last >= 128:
        last = (2 * last) ^ 27
    else:
        last = 2 * last;
    print("Iterator", i)
    print("Value", last)