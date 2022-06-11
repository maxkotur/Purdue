import perceptron
import svm
import predict
import numpy

import unittest


class TestAlgorithms(unittest.TestCase):

    def setUp1(self):
        numpy.set_printoptions(precision=4)

        self.X = numpy.array([[-3, 2],
                              [-2, 1.5],
                              [-1, 1],
                              [0, 0.5],
                              [1, 0]])

        self.y = numpy.array([[1], [1], [1], [-1], [-1]])

    def setUp2(self):
        numpy.set_printoptions(precision=4)
        self.X = numpy.array([[-2, 2, 0],
                              [-3, -1.5, -2],
                              [-1, 1, 4],
                              [1, -0.5, 5],
                              [2, 0, -2]])
        self.y = numpy.array([[1], [1], [1], [-1], [-1]])

    def setUp3(self):
        self.X = numpy.array(([[-2, 2, 0, -2, 2, 0, 4],
                               [-3, -1.5, -2, 6, 5, 1, 4],
                               [-1, 1, 4, 0, 5, -4, 5],
                               [1, -0.5, 5, -9, -9, 0, 0],
                               [2, 0, -2, -4.5, 3, 3, 1]]))
        self.y = numpy.array([[1], [1], [1], [-1], [-1]])
        numpy.set_printoptions(precision=4)

    def testPerceptron2DimData(self):
        self.setUp1()
        print("perceptron 1")
        correct = list()
        correct.append((numpy.array([[-3.], [1.5]]), 1))
        correct.append((numpy.array([[-3.], [1.]]), 2))
        correct.append((numpy.array([[-3.], [0.5]]), 3))
        correct.append((numpy.array([[-3.], [0.]]), 4))
        correct.append((numpy.array([[-3.], [-0.5]]), 5))
        correct.append((numpy.array([[-3.], [-0.5]]), 6))

        for i in range(1, 7):
            ret = perceptron.run(i, self.X, self.y)
            print(ret, correct[i - 1])
            arrayeq = numpy.allclose(ret[0], correct[i-1][0])
            arrmsg = "arrays not equal, actual:" + \
                str(ret[0]) + " | expected: " + str(correct[i-1][0])
            self.assertTrue(arrayeq, arrmsg)
            self.assertEqual(ret[1], correct[i - 1][1], "prediction not correct")

    def testPerceptron3DimData(self):
        self.setUp2()
        print("perceptron 3")
        correct = list()
        correct.append((numpy.array([[-2.], [2.], [0.]]), 1))
        correct.append((numpy.array([[-2.], [2.], [0.]]), 2))
        correct.append((numpy.array([[-2.], [2.], [0.]]), 2))

        for i in range(1, 3):
            ret = perceptron.run(i, self.X, self.y)
            print(ret, correct[i - 1])
            arrayeq = numpy.allclose(ret[0], correct[i-1][0])
            arrmsg = "arrays not equal, actual:" + \
                str(ret[0]) + " | expected: " + str(correct[i-1][0])
            self.assertTrue(arrayeq, arrmsg)
            self.assertEqual(ret[1], correct[i - 1][1], "prediction incorrect")

    def testSVM3DimData(self):
        self.setUp2()

        correct = numpy.array([[-0.6238], [0.4837], [-0.0269]])
        ret = svm.run(self.X, self.y)
        equal = numpy.allclose(ret, correct, atol=1e-4, rtol=1e-4)
        arrmsg = "arrays not equal. expected: " + \
            str(correct) + " | actual:" + str(ret)
        self.assertTrue(equal, arrmsg)

    def testSVM2DimData(self):
        self.setUp1()
        print("svm 1")
        correct = numpy.array([[-3.], [-2.]])
        ret = svm.run(self.X, self.y)
        equal = numpy.allclose(ret, correct, atol=1e-4, rtol=1e-4)
        arrmsg = "arrays not equal. expected: " + str(correct) + " | actual:" + str(ret)
        self.assertTrue(equal, arrmsg)

    def testPredict2DimDataPerceptron(self):
        self.setUp1()

        correct_perc = numpy.array([[-3.], [-0.5]])
        theta_perc, num = perceptron.run(10, self.X, self.y)

        perc_eq = numpy.allclose(theta_perc, correct_perc)
        arrmsg = "perceptron arrays not equal, \nactual:" + \
            str(theta_perc[0]) + " | expected: " + str(correct_perc)
        self.assertTrue(perc_eq, arrmsg)

        self.assertEqual(predict.run(theta_perc, numpy.array(
            [[1], [-2]])), -1.0, "perceptron prediction 1 incorrect")
        self.assertEqual(predict.run(theta_perc, numpy.array(
            [[-2], [2]])), 1.0, "perceptron prediction 2 incorrect")
        
    
    def testPredict2DimDataSVM(self):
        self.setUp1()
        correct_svm = numpy.array([[-3.], [-2.]])
        theta_svm = svm.run(self.X, self.y)
        svm_eq = numpy.allclose(theta_svm, correct_svm)

        arrmsg = "svm arrays not equal, \nactual:" + \
            str(theta_svm) + "\nexpected:" + str(correct_svm)
        self.assertTrue(svm_eq, arrmsg)

        self.assertEqual(predict.run(theta_svm, numpy.array(
            [[1], [-2]])), 1.0, "svm prediction incorrect")

    def testPerceptron7DimData(self):
        self.setUp3()

        correct = list()
        correct.append(
            (numpy.array([[-4.], [2.], [2.], [2.5], [-1.], [-3.], [3.]]), 1))
        correct.append(
            (numpy.array([[-4.], [2.], [2.], [2.5], [-1.], [-3.], [3.]]), 2))
        correct.append(
            (numpy.array([[-4.], [2.], [2.], [2.5], [-1.], [-3.], [3.]]), 2))

        for i in range(1, 3):
            ret = perceptron.run(i, self.X, self.y)
            print(ret, correct[i - 1])
            arrayeq = numpy.allclose(
                ret[0], correct[i - 1][0], atol=1e-4, rtol=1e-4)
            arrmsg = "arrays not equal, actual:" + \
                str(ret[0]) + " | expected: " + str(correct[i-1][0])

            self.assertTrue(arrayeq, arrmsg)
            self.assertEqual(ret[1], correct[i - 1][1], "prediction not correct")

    def testSVM7DimData(self):
        self.setUp3()
        correct = numpy.array(
            [[-0.1709], [0.0973], [0.0543], [0.0976], [0.0193], [-0.1078], [0.1551]])
        ret = svm.run(self.X, self.y)
        equal = numpy.allclose(ret, correct, atol=1e-4, rtol=1e-4)
        arrmsg = "arrays not equal, actual:" + \
            str(ret) + " | expected: " + str(correct)
        self.assertTrue(equal, arrmsg)


if __name__ == "__main__":
    unittest.main()
