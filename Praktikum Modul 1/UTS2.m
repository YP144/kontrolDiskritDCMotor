gs = tf(3.37717,[0.72166 1])
waktuCacah = 0.05;
gz = c2d(gs,waktuCacah,"tustin")
step(feedback(gz,1));
stepinfo(feedback(gz,1))