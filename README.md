# mobell
IoT Example Application for Android integration into home Door-Bell

Very early, just basic skeleton of real concept. 

### Done:

1. Device announces BOIP service using mDNS.
2. Supports /reg?dev_id=??? to store value
3. Subsequent /poll returns the stored value.


# TODO
1. Put some storage model to registration(s)
2. UDP Multicast broadcast of events, e.g. Phone Service/App has entered or left the network.
3. Short poll to device by APP as a heartbeat to keep presence of device(s)
3. Create full API, complete code and describe how an event broadcast is formulated.
4. Add GPIO for doorbell integration.
5. Add to API for broadcast of button push, and events to ring the doorbell by App.