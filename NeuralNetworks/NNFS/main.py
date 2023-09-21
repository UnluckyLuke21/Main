inputs = [1,2,3,4]
targets = [12,14,16,18]

w = 0.1
b = 0.3
lr = 0.1
epochs = 100

def predict(i):
    return w * i + b

print(predict(2))

# Train the Network:
for _ in range(epochs):
    pred = [predict(i) for i in inputs]
    errors = [(p -t) ** 2 for p, t in zip(pred, targets)]
    cost = sum(errors) / len(targets)

    print(f"Weight: {w:.2f}, Cost: {cost:.2f}")

    # Backpropagation:
    errors_d = [2 * (p - t) for p, t in zip(pred, targets)]
    weights_d = [e * i for e, i in zip(errors_d, inputs)]

    bias_d = [e * 1 for e in errors_d]

    w -= lr * sum(weights_d) / len(weights_d)
    b -= lr * sum(bias_d) / len(bias_d)

# Test the Network:
tinput = [5, 6]
ttargets = [20, 22]
pred = [predict(i) for i in tinput]
for i, t, p in zip(tinput, ttargets, pred):
    print(f"Input:{i}, Target:{t}, Pred:{p:.4f}")
