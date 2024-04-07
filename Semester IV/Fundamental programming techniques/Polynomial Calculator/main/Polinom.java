package org.example;

import java.util.Map;
import java.util.TreeMap;
import java.util.Collections;

public class Polinom {

    private Map<Integer, Integer> polinom;

    public Polinom(Map<Integer, Integer> polinom) {
        this.polinom = new TreeMap<>(polinom);
    }

    public Map<Integer, Integer> getPolinom() {
        return polinom;
    }

    public void setPolinom(Map<Integer, Integer> polinom){
        this.polinom = polinom;
    }

    public Map<Integer, Integer> addPolynomials(Map<Integer, Integer> p1, Map<Integer, Integer> p2) {
        return Operator.addPolinom(p1, p2);
    }

    public Map<Integer, Integer> subtractPolynomials(Map<Integer, Integer> p1, Map<Integer, Integer> p2) {
        return Operator.substractPolinom(p1, p2);
    }

    public Map<Integer, Integer> multiplyPolynomials(Map<Integer, Integer> p1, Map<Integer, Integer> p2) {
        return Operator.multiplyPolinom(p1, p2);
    }

    @Override
    public String toString(){

        StringBuilder sb = new StringBuilder();
        boolean isFirstTerm = true;
        TreeMap<Integer, Integer> sortedMap = new TreeMap<>(Collections.reverseOrder());
        sortedMap.putAll(polinom);

        for (int exponent : sortedMap.keySet()) {
            int coefficient = sortedMap.get(exponent);
            if (coefficient != 0) {
                if (!isFirstTerm) {
                    sb.append(coefficient > 0 ? " + " : " - ");
                    coefficient = Math.abs(coefficient);
                } else {
                    isFirstTerm = false;
                    if (coefficient < 0) {
                        sb.append("-");
                        coefficient = -coefficient;
                    }
                }
                if (coefficient != 1 || exponent == 0) {
                    sb.append(coefficient);
                }
                if (exponent > 0) {
                    sb.append("x");
                    if (exponent > 1) {
                        sb.append("^").append(exponent);
                    }
                }
            }
        }
        if (sb.length() == 0) {
            sb.append("0");
        }
        return sb.toString();
    }

    public static Polinom toPolynomial(String input) {
        Map<Integer, Integer> polinom = new TreeMap<>();
        String[] terms = input.split("(?=[-+])");
        for (String term : terms) {
            term = term.trim();
            int coefIndex = term.indexOf("x");
            if (coefIndex == -1) {
                int constant = Integer.parseInt(term);
                polinom.put(0, constant);
            } else {
                int exponentIndex = term.indexOf("^");
                int coef = 1;
                int exponent = 1;
                if (coefIndex == 0 || term.charAt(coefIndex-1) == '+') {
                    coef = 1;
                } else if (term.charAt(coefIndex-1) == '-') {
                    coef = -1;
                } else {
                    coef = Integer.parseInt(term.substring(0, coefIndex));
                }
                if (exponentIndex != -1) {
                    exponent = Integer.parseInt(term.substring(exponentIndex + 1));
                }
                polinom.put(exponent, coef);
            }
        }
        return new Polinom(polinom);
    }
}

