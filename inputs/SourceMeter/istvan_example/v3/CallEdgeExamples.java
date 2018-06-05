// 1.0 (03.11) Istvan
// 1.1 (03.13) Istvan: interface default method
// 1.2 (03.17) epengo: ANONIM_TEST

class M {
	public static void sg(String s) {
		System.out.println(s);
	}
}

interface Interface {
	void foo();
	void goo();
  default void hoo() {
    M.sg("Interface.hoo()");
  }
}

class Base {
	public void base() {
		M.sg("Base.base()");
	}
}

abstract class Abstract extends Base implements Interface {
	public void foo() {
		M.sg("Abstract.foo()");
	}
}

class Child1 extends Abstract implements Interface {
	public void goo() {
		M.sg("Child1.goo()");
	}
	public void foo() {
		M.sg("Child1.foo()");
	}
	public void child1() {
		M.sg("Child1.child1()");
	}
}

class Child2 extends Abstract implements Interface {
	public void goo() {
		M.sg("Child2.goo()");
	}
  public void hoo() {
    M.sg("Child2.hoo()");
  }

}


class Helper {
	public void interfaceTest(Interface interf) {
		M.sg("Helper.interfaceTest(Interface)");
		interf.foo();
	}
	public <T extends Interface> void genericMethod(T t) {
		M.sg("Helper.genericMethod(T)");
		t.foo();		
	}
	public Child1 instantiateChild1() {
		M.sg("Helper.instantiateChild1()");
		return new Child1();
	}
}


class Generic1<T extends Interface> {
	public void generic(T t) {
		M.sg("Generic1.generic(T)");
		t.foo();
	}
}

class Generic2<T extends Interface, K extends Generic1<T>> {
	public void generic(T t, K k) {
		M.sg("Generic2.generic(T, K)");
		t.foo();
		k.generic(t);
	}
}

class Generic3 extends Generic1<Child1> {
	public void foo() {
		M.sg("Generic3.foo()");
		generic(new Child1());
	}
}

class Outer {
	public void inner() {
		M.sg("Outer.foo()");
		new Inner().inner();
	}
	
	public class Inner {
		public void inner() {
			M.sg("Outer.Inner.foo()");
		}
	}
	
	public static class Nested {
		public static void staticNested() {
			M.sg("Outer.Nested.staticNested()");
		}

		public void nested() {
			M.sg("Outer.Nested.nested()");
		}
	}
}

class Init {
	Interface i1, i2 = new Helper().instantiateChild1(), i3, i4;

	{
		M.sg("Init.{}");
		i1 = new Child1();
	}
	{
		i3 = new Child2();
	}
	public Init(Interface i) {
		M.sg("Init.Init(Interface)");
		i4 = i; 
	}
}

class StaticInit {
	static Interface i1, i2;

	static {
		M.sg("StaticInit.{}");
		i1 = new Helper().instantiateChild1();
	}
	static {
		i2 = new Child2();
	}
	
	static void staticInit() {
		M.sg("StaticInit.staticInit()");
	}
}

interface Lambda {
  boolean compare(int a1, int a2);
}

class Constructor {
	Constructor() {
		M.sg("Constructor.Constructor()");
	}
}

class Overload {
	void foo() {
		M.sg("Overload.foo()");
	}
	void foo(int i) {
		M.sg("Overload.foo(int)");
	}
	<T> void foo(T t) {
		M.sg("Overload.foo(T)");
	}
	void foo(int i, Object... objects ) {
		M.sg("Overload.foo(int, Object...)");
	}
}

class ForParser {
	/* void notMethod1() {} */
	/*
	 void notMethod2() {}
	 */
	//  void notMethod3() {}
	// // void notMethod4() {}
	// /*  */ void notMethod5() {}
	String s1 = "void notMethod6() {}";
	String s2 = \u0022 void notMethod7() {} \u0022;
	
	\u0076\u006F\u0069\u0064 \u0066\u006F\u006F() { // void foo()
		M.sg("\u0076\u006F\u0069\u0064 ForParser.\u0066\u006F\u006F()");
	}

	\u0076\u006F\u0069\u0064 goo() {
		M.sg("\u0076\u006F\u0069\u0064 ForParser.goo()");
	}
	
	Generic2<Child2, Generic1<Child2>> validMethod(Child2 c, Generic1<Child2> g, Class<?>... objects) {
		M.sg("Generic2<Child2, Generic1<Child2>> ForParser.validMethod(Child2, Generic1<Child2>, Class<?>... )");
		
		Generic2<Child2, Generic1<Child2>> local = new Generic2<Child2, Generic1<Child2>>();
		local.generic(c,  g);
		return local;
	}
	
	<T, K extends Child2> Generic2<Child2, Generic1<Child2>> validGenericMethod(K c, Generic1<K> g, Class<?>... objects) {
		M.sg("<T, K extends Child2> Generic2<Child2, Generic1<Child2>> ForParser.validGenericMethod(K, Generic1<K>, Class<?>...)");
		
		Generic2<Child2, Generic1<Child2>> local = new Generic2<Child2, Generic1<Child2>>();
		local.generic(c,  new Generic1<Child2>());
		return local;
	}
}

/* - polimorphic call
 * - inner class
 * - anonim class
 * - nested class
 * - local calss
 * - generic class
 * - generic method
 * - init
 * - static init
 * - initialization
 * - lambda
 * - constructor
 * - kikommentezett
 * - overload
 */
public class CallEdgeExamples {
	
	private final Base ANONIM_TEST = new Base() {
        public void base() {
            M.sg("\nANONIM_TEST: not so base");
        }
    };
	public static void main(String[] args) {
		CallEdgeExamples c = new CallEdgeExamples();
		c.polimorphic();
		c.innerClass();
		c.anonim();
		c.nested();
		c.local();
		c.generic();
		c.init();
		c.lambda();
		c.contructor();
		c.overload();
		c.parser();
		c.ANONIM_TEST.base();
	}
	
	void polimorphic() {
		M.sg("\nTest: polimorphic");
		
		Interface i1 = new Child1();
		i1.foo();
		i1.goo();
    i1.hoo();
		Abstract a1 = new Child1();
		a1.foo();
		new Child1().foo();
		
		Interface i2 = new Child2();
		i2.foo();
    i2.hoo();
		
		new Helper().interfaceTest(a1);
	}
	
	void innerClass() {
		M.sg("\nTest: inner class");

		Outer outer = new Outer();
		outer.inner();
	}
	
	void anonim() {
		M.sg("\nTest: anonim class");
		
		Child1 c1 = new Child1() {
			public void foo() {
				M.sg("Child1_anonim.foo()");
			}
		};
		c1.foo();
		c1.goo();
		
		Generic1<Child1> g2 = new Generic1<Child1>() {
			public void generic(Child1 c) {
				M.sg("Generic<Child1>_anonim.generic(Child1)");
				c.foo();
			}
		};
		g2.generic(c1);
	}
	
	void nested() {
		M.sg("\nTest: nested class");
		
		new Outer.Nested().nested();
		Outer.Nested.staticNested();
	}

	void local() {
		M.sg("\nTest: local class");
		
		class Local {
			public void foo() {
				M.sg("CallEdgeExamples.Local.foo()");
			}
		};
		new Local().foo();
	}
	
	void generic() {
		M.sg("\nTest: generic class/method");
		
		Generic1<Child1> g1 = new Generic1<Child1>();
		g1.generic(new Child1());

		Generic1<Child2> g2 = new Generic1<Child2>();
		g2.generic(new Child2());
		
		Generic2<Child2, Generic1<Child2>> g3 = new Generic2<Child2, Generic1<Child2>>();
		g3.generic(new Child2(), g2);
		
		new Generic3().foo();
		
		new ForParser().validMethod(new Child2(), g2, Integer.class).generic(new Child2(), g2);
		new ForParser().validGenericMethod(new Child2(), g2, Integer.class).generic(new Child2(), g2);
		
		new Helper().genericMethod(new Child2());
	}
	
	void init() {
		M.sg("\nTest: generic class/method");
		
		new Init(new Child1());
		StaticInit.staticInit();
	}
	
	void contructor() {
		M.sg("\nTest: constructor");

		new Constructor();
	}
	
	void lambda() {
		M.sg("\nTest: generic class/method");

		Lambda l = (a1, a2) -> { M.sg("CallEdgeExamples->lambda(int, int)"); return a1 > a2;};
		l.compare(2, 5);
	}
	void overload() {
		M.sg("\nTest: overload");
		
		Overload o = new Overload();
		o.foo();
		o.foo(3);
		o.foo(o);
		o.foo(3, o);
	}
	
	void parser() {
		M.sg("\nTest: parser");
		
		ForParser f = new ForParser();
		f.foo();
		\u0066.\u0066\u006F\u006F();
		f.goo();
	}
	
}
