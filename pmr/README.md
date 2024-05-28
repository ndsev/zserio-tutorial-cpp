# Custom Memory Management using Polymorphic Allocators

By default, C++ generated objects use [`std::allocator`](https://en.cppreference.com/w/cpp/memory/allocator),
which doesn't allow any custom memory management. However, C++ generator supports as well
[`zserio::pmr::PolymorphicAllocator`](https://zserio.org/doc/runtime/latest/cpp/PolymorphicAllocator_8h.html),
which is inspired by the
[`std::pmr::polymorphic_allocator`](https://en.cppreference.com/w/cpp/memory/polymorphic_allocator) from C++17
standard.

To enable Zserio polymorphic allocators, it is necessary to specify command line
option `-setCppAllocator polymorphic`.

Using polymorphic allocators allows custom memory management in few simple steps:

- At first, the application must implement user memory resource by inheriting
  [`zserio::pmr::MemoryResource`](https://zserio.org/doc/runtime/latest/cpp/MemoryResource_8h.html).
- Then, the application must construct user memory resource.
- Created user memory resource must be used to construct Zserio polymorphic allocator.
- The constructed Zserio polymorphic allocator must be passed to the Zserio object constructor.

> Note that the Zserio polymorphic allocator has empty constructor which uses default memory resource
> with standard C++ operator new and delete! To prevent this, it's possible to call
> `zserio::pmr::setDefaultResource` which takes the default memory resource which will be used
> when no allocator is passed.

## Custom Memory Resource

An example of custom [memory resource](https://zserio.org/doc/runtime/latest/cpp/MemoryResource_8h.html) which
can be found in [`StaticMemoryResource.h`](src/StaticMemoryResource.h). Each custom memory resources has to
implement the three abstract methods:

```cpp
void* doAllocate(size_t bytes, size_t align) override
{
    const size_t alignMod = static_cast<size_t>(m_nextPtr - m_buffer.begin()) % align;
    if (alignMod != 0)
        m_nextPtr += align - alignMod;

    void* const ptr = &(*m_nextPtr);
    m_nextPtr += bytes;

    const size_t usedBytes = static_cast<size_t>(m_nextPtr - m_buffer.begin());
    if (usedBytes > BUFFER_SIZE)
        throw zserio::CppRuntimeException(m_name) << ": Buffer overflow (" << usedBytes << ")!";

    return ptr;
}

void doDeallocate(void*, size_t bytes, size_t) override
{
    // release the memory - not implemented by the StaticMemoryResource
}

bool doIsEqual(const MemoryResource& other) const noexcept override
{
    return this == &other;
}
```

The memory resource can be later used by `zserio::pmr::PolymorphicAllocator`, which takes pointer to the memory
resource in (implicit) constructor.

The memory resource can be also set as a default memory resource using
`::zserio::pmr::setDefaultResource` method, which causes that all code which uses
`zserio::pmr::PolymorphicAllocator` will use it when no memory resource is provided.

## Using Custom Memory Resource

Again, everything is already prepared for you within this repository in the `pmr` folder.

Let's modify the tutorial source code to use our static memory resource. At first, we have to regenerate
sources with `-setCppAllocator polymorphic`. Note that we have to slightly change types of STL containers -
`std::vector` becomes `zserio::pmr::vector` and `std::string` become `zserio::pmr::string`. Those are just
convenience wrappers provided in `zserio::pmr` namespace to use correct allocators.

> Note that in most places we could avoid these changes if we were using `auto` keyword, but we use the full
> types for demonstration purposes.

Now we will create the two memory resources in order to compare the two basic approaches - providing allocator
to all objects manually vs. setting the default memory resource.

```cpp
StaticMemoryResource<32> memoryResource("Joe's memory resource");

// memory resource which will be used by polymorphic allocators when no memory resource is provided
StaticMemoryResource<32> defaultMemoryResource("Default memory resource");
zserio::pmr::setDefaultResource(&defaultMemoryResource);

```

Then we will change the `writeJoe` method to take the allocator and thus we demonstrate the first approach:

```cpp
void writeJoe(const std::string& employeeFile,
        const zserio::pmr::PropagatingPolymorphicAllocator<uint8_t>& allocator)
{
    /* declare an employee - provide the allocator */
    tutorial::Employee joe(allocator);

    /* fill some basic type fields */
    joe.setAge(32);
    /* for longer strings the allocator would be necessary */
    joe.setName(zserio::pmr::string("Joe Smith", allocator));
    joe.setSalary(5000);

    /* set an enum value, in this case the role */
    joe.setRole(tutorial::Role::DEVELOPER);

    /* declare an array which holds a zserio struct - provide the allocator to vector */
    zserio::pmr::vector<tutorial::Experience> skills(allocator);

    /* declare and fill the struct Experience - provide the allocator */
    tutorial::Experience skill1(allocator);
    skill1.setYearsOfExperience(8);
    skill1.setProgrammingLanguage(tutorial::Language::CPP);
    skills.push_back(skill1);

    /* fill a second one... (and provide the allocator) */
    tutorial::Experience skill2(allocator);
    skill2.setYearsOfExperience(4);
    skill2.setProgrammingLanguage(tutorial::Language::PYTHON);
    skills.push_back(skill2);

    joe.setSkills(skills);

    /** serialize to file - will allocate a bit buffer using the default memory resource */
    zserio::serializeToFile(joe, employeeFile);
}
```

> Note that we have to provide the allocator to all generated objects and to all objects which can dynamically
> allocate, such as `string`s and `vector`s.

When calling the `writeJoe` method, we can just provide pointer to the desired memory resource since polymorphic
allocators have an implicit constructor from it:

```cpp
writeJoe(employeeFile, &memoryResource);
```

We can left the other methods unchanged (except the STL containers types) since we want to demonstrate
the second approach - using the default memory resource. The generated objects now take polymorphic allocators
in constructors which will request the default memory resource automatically - see
[`zserio::pmr::PolymorphicAllocator`](https://zserio.org/doc/runtime/latest/cpp/PolymorphicAllocator_8h_source.html)
default constructor.

For purposes of this tutorial we added some statistical functions to the `StaticMemoryResource` and thus we
can see some reporting:

```
$ ./ZserioTutorialCppPmr write_joe
Joe's memory resource: numAllocations=3, numDeallocations=3, totalAllocatedSize=10
Default memory resource: numAllocations=1, numDeallocations=1, totalAllocatedSize=18
```

> Note that there is an extra allocation of a `BitBuffer` within the call of
> `zserio::serializeToFile(joe, employeeFile)`, where we use the default allocator since it's not part of
> the Joe's data.

```
$ ./ZserioTutorialCppPmr read
Name: Joe Smith
Age: 32
Salary: 5000
Role: DEVELOPER
Skill: Language CPP, 8 years
Skill: Language PYTHON, 4 years
Bit size of employee: 137
Joe's memory resource: numAllocations=0, numDeallocations=0, totalAllocatedSize=0
Default memory resource: numAllocations=1, numDeallocations=1, totalAllocatedSize=4
```

> We left the read method here to use the default memory resource which allocates the `vector` for the employee's
> skills.

> Note that the `deserializeFromFile` method uses `zserio::BitBuffer` with the default `std::allocator` and thus
> it's not calculated in the report.

```
$ ./ZserioTutorialCppPmr write_boss
Joe's memory resource: numAllocations=0, numDeallocations=0, totalAllocatedSize=0
Default memory resource: numAllocations=1, numDeallocations=1, totalAllocatedSize=12
```

> Note that there is again an extra allocation of a `BitBuffer` within the call of
> `zserio::serializeToFile(boss, employeeFile)`.

```
$ ./ZserioTutorialCppPmr read
Name: Boss
Age: 43
Salary: 9000
Role: TEAM_LEAD
Bonus: 10000
Bit size of employee: 89
Joe's memory resource: numAllocations=0, numDeallocations=0, totalAllocatedSize=0
Default memory resource: numAllocations=0, numDeallocations=0, totalAllocatedSize=0
```

> Note that the boss doesn't have any dynamic fields.

Using the default memory resource seems to be much easier but note that by using it you can loose control over
the memory allocations since it will be automatically used for all objects where you don't provide an
allocator manually. Providing allocators manually gives you full control over the allocations but still you
can easily forget to provide an allocator on some places:

```cpp
// unchanged, this would use the default memory resource in case of a longer name, since
// zserio::pmr::string will be instantiated
joe.setName("Joe Smith");
```

```cpp
// vector takes the allocator in constructor, this would also use the default memory resource
zserio::pmr::vector<tutorial::Experience> skills;
```

To catch such mistakes the application can set some kind of "invalid" memory resource as the default,
which will e.g. throw an exception when it's used.

> Note that zserio objects reading mechanism is designed to allocate continuous memory without fragmentation,
> so that the application can easily read the whole BLOB into the consecutive memory as can be seed on the
> examples above.

Inspiration and more implementation details how to use memory resource and polymorphic allocators
can be found in our
[test utilities](https://github.com/ndsev/zserio/blob/master/test/utils/cpp/test_utils/MemoryResources.h)
and in
[polymorphic allocators test](https://github.com/ndsev/zserio/blob/master/test/arguments/set_cpp_allocator/cpp/ComplexAllocationTest.cpp).

## Allocator propagating copy and move

The allocators by definition are not required to be propagated when a container is copied or assigned. See
[AllocatorAwareContainer](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer). Therefore,
special care must be taken, when an instance of class, that uses an allocator, is copy-constructed or
move-constructed.

The `zserio::pmr::PolymorphicAllocator` is designed by the
[`std::polymorphic_allocator`](https://en.cppreference.com/w/cpp/memory/polymorphic_allocator) and as such it
does not propagate on copy construction or assignment.

There is also `zserio::pmr::PropagatingPolymorphicAllocator`, which does propagate on container copy
constructions or assignment. This may simplify the implementation, but the runtime and generated classes should
be prepared to support non-propagating version of the allocator.

The allocator-aware containers, which are the standard containers and containers in zserio runtime
(i.e. `zserio::AnyHolder`, `zserio::HeapOptionalHolder`), have all versions of constructor with additional
allocator parameter. However, the containers does not propagate the allocator to its stored objects.
For example, if `std::vector` is copied using its constructor with additional allocator parameter,
the new allocator is only used for allocation of the storage of the vector itself, but the stored objects are
copied using the regular copy constructor. So in case of non-propagating allocator
(like the `zserio::pmr::PolymorphicAllocator`), default-constructed allocator is used for it.

To make it possible to copy the generated classes with allocators without falling back to the
default-constructed allocator, the runtime contains few supporting utilities -
`zserio::allocatorPropagatingCopy`, which performs the "allocator deep copy" and `zserio::PropagateAllocator`
which can be used to mark constructors that performs "allocator deep copy" as described below.

The copy constructor of generated classes does not propagate the allocator to the nested classes.
This would be too confusing as the standard containers nor other standard classes does this. Therefore,
**in case of non-propagating allocator, the standard copy constructor uses default-constructed allocator**!

The generated classes (unlike the containers) does not have the extended copy and move constructors with
additional allocator parameters. This could be too confusing, it would not propagate the allocator anyway and
the move constructor with additional allocator parameter may fall back to copy everything in some cases
(or ignore the allocator parameter).

All generated classes has an extended copy constructor with allocator parameter, but this constructor also have
a `PropagateAllocator` tag. This constructor propagates allocator to all nested classes, and due to the
`PropagateAllocator` tag, it is more obvious what does the constructor do and cannot be confused with the
regular extended copy/move constructors. These constructors copy all its members using
`zserio::allocatorPropagatingCopy`.

I.e. **to copy the whole "tree" of structures with a different allocator, the constructor with
`PropagateAllocator` tag can be used**.

The `zserio::allocatorPropagatingCopy` behaves as follows:

* If the type is `zserio::HeapOptionalHolder`, `zserio::AnyHolder` or `std::vector`, the input allocator is passed
  to to its constructor and stored object(s) are copied/moved using the zserio::allocatorPropagatingCopy with the
  same allocator.

* If the type is `zserio::InplaceOptionalHolder`, the stored object is copied/moved using the
  `zserio::allocatorPropagatingCopy` with the input allocator.

* If the type supports allocator (i.e. `std::uses_allocator` yields true for it) and has a constructor with
  `PropagateAllocator` tag, such constructor is used. This applies on generated classes.

* If the type supports the allocator (ie. std::uses_allocator yields true for it) but does not have a
  constructor with PropagateAllocator tag, the input allocator is passed to its copy constructor. For example,
  this applies on std::string.

* In other cases, the object is just copied without the allocator being used.
