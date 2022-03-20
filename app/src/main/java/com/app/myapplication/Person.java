package com.app.myapplication;

public class Person {

    private String name;
    private int age;
    private AddRess add;

    public static class AddRess{
        private String province;
        private String city;
        private int cityCode;

        public AddRess() {
        }

        public AddRess(String province, String city, int cityCode) {
            this.province = province;
            this.city = city;
            this.cityCode = cityCode;
        }

        @Override
        public String toString() {
            return "AddRess{" +
                    "province='" + province + '\'' +
                    ", city='" + city + '\'' +
                    ", cityCode=" + cityCode +
                    '}';
        }
    }

    public Person() {
    }

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public AddRess getAdd() {
        return add;
    }

    public void setAdd(AddRess add) {
        this.add = add;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", add=" + add +
                '}';
    }
}
