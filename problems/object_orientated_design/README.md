# Object-Orientated Design

## How to Approach

### Step 1: Handle Ambiguity
Often intentionally vague, make ask clarifying questions.

Who is going to use it and how will they use it. Potentially 6 Ws, who what where when how why.
* coffee maker? industrial, thousands per hour, or retail? one drink, 10? 100 customers, 1? simple machine for elderly, or complex?

### Step 2: Define Core Objects
Consider what they are. For restaurant: Table, Guest, Party, Order, Meal, Employee, Server, Host

### Step 3: Analyze Relationships
Which objects are members of other ones? Do any inherit from others? Are relationships many to many or one to one?
* Party should have array of guests
* Server and Host inherit Employee
* Each Table has one Party, but each Party may have multiple tables
* There is one Host for the Restaurant

But careful for bad assumptions, one table may have multiple parties in trendy communal restaurants.

### Step 4: Investigate Actions
Should now have basic outline. Consider key actions objects will take and how they relate to each other. Maybe forgotten some.
Party walks into restuarant, guest requests table from host. host looks up reservation and if exists add party to table. else party added to end of list.
when party leaves table freed assigned to new party in list.

### Design Patterns
#### Singleton Pattern
Class only has one instance, access instance through app. "global object", one instance. Restaurant for example  
```
public class Restaurant {
  private Restaurant _instance = null;
  public static Restaurant getInstance() {
    if (_instance == null) {
      _instance = new Restaurant();
    }
    return _instance;
  }
}
```
#### Factory Method
factory method offers interface for creating instance of class, with subclasses deciding which class to instantiate. Could implement w/ creator class abstract, not providing implementation for Factory method. Or, Creator class concrete provides implmeentation for Factory method. Then, Factory takes parameter represendting class to instantiate.

```
public class CardGame {
  public static CardGame createCardGame(GameType type) {
    if (type == GameType.Poker) {
      return new PokerGame();
    } else if (type == GameType.BlackJack) {
      return new BlackJackGame();
    }
    return null;
  {
}
```
