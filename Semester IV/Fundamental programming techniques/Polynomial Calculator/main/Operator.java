package org.example;

import java.util.Map;
import java.util.TreeMap;

public class Operator {

    public static Map<Integer, Integer> addPolinom(Map<Integer, Integer> p1, Map<Integer, Integer> p2){
        Map<Integer, Integer> result = new TreeMap<>();
        for (int exponent : p1.keySet()) {
            if (p2.containsKey(exponent)) {
                result.put(exponent, p1.get(exponent) + p2.get(exponent));
            }
            else {
                result.put(exponent, p1.get(exponent));
            }
        }
        for(int exponent : p2.keySet()) {
            if(!p1.containsKey(exponent)) {
                result.put(exponent, p2.get(exponent));
            }
        }
        return result;
    }

    public static Map<Integer, Integer> substractPolinom(Map<Integer, Integer> p1, Map<Integer, Integer> p2){
        Map<Integer, Integer> result = new TreeMap<>();
        for(int exponent : p1.keySet()) {
            if(p2.containsKey(exponent)) {
                result.put(exponent, p1.get(exponent) - p2.get(exponent));
            }
            else {
                result.put(exponent, p1.get(exponent));
            }
        }
        for(int exponent : p2.keySet()) {
            if(!p1.containsKey(exponent)) {
                result.put(exponent, -p2.get(exponent));
            }
        }
        return result;
    }

    public static Map<Integer, Integer> multiplyPolinom(Map<Integer, Integer> p1, Map<Integer, Integer> p2) {
        Map<Integer, Integer> result = new TreeMap<>();
        for (int exp1 : p1.keySet()) {
            for (int exp2 : p2.keySet()) {
                int exponent = exp1 + exp2;
                int coefficient = p1.get(exp1) * p2.get(exp2);
                if (result.containsKey(exponent)) {
                    result.put(exponent, result.get(exponent) + coefficient);
                } else {
                    result.put(exponent, coefficient);
                }
            }
        }
        return result;
    }

}
