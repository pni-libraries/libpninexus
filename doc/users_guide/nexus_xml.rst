===========
XML support
===========

NeXus files can grow quite complex it would be rather tedious to express
the structure of such a file entirely in code. 
*libpniio* provides a way to create NeXus structures from XML. Like HDF5, 
XML structures data in a tree like hierarchy, making it the perfekt ASCII 
representation for a NeXus file. 

Generating objects
==================

The XML content can come from two sources 

* a file 
* or from a string. 

Using the XML interface is rather simple. Consider that we have the structure
of the file expressed as XML and stored in a file :file:`file_structure.xml`
using this is simply  

.. code-block:: cpp

   hdf5::node::Group root_group = file.root(); 
   
   nexus::xml::create_from_file(root_group,"file_structure.xml");
   
Alternatively you could use XML content from a string 

.. code-block:: cpp

   hdf5::node::Group instrument = hdf5::node::get_node(root_group,"/entry/instrument");
   
   std::string detector_struct = create_detector_structure();
   nexus::xml::create_from_string(instrument,detector_struct); 

As can be seen from this example the XML data must not contain the entire 
file structure. Instead it would be possible to provide separate XML files 
with different components of the file. 
Consider here for instance the following files 

+-------------------------+-----------------------------+
| file                    | content description         |
+=========================+=============================+
| :file:`basic_file.xml`  | the basic file structure    |
+-------------------------+-----------------------------+
| :file:`detector_1d.xml` | structure for a 1d detector |
+-------------------------+-----------------------------+
| :file:`detector_2d.xml` | structure for a 2d detector |
+-------------------------+-----------------------------+
   
Code which usese this setup could look like this 

.. code-block:: cpp

   hdf5::file::File file = ... ;
   hdf5::node::Group root_group = file.root(); 
   
   nexus::xml::create_from_file(root_group,"basic_file.xml");
   hdf5::node::Group instrument = hdf5::node::get_node(root_group,"/entry/instrument");
   
   switch(detector_setup)
   {
      case DetectorType::LINEAR:
         nexus::xml::create_from_file(instrument,"detector_1d.xml");
         break;
      case DetectorType::AREA:
         nexus::xml::create_from_file(instrument,"detector_2d.xml");
   }
   


It should be mentioned that currently *libpniio* does not use a validating 
parser which makes error detection rather difficult. 

%

%%%============================================================================
\subsection{High level XML interface}\label{sec:xml:highlevel}

The high-level XML interface basically consists of two function templates 
\begin{description}
\item[xml\_to\_nexus] which creates \nexus\ objects from XML templates
\item[nexus\_to\_xml] which generates XML from \nexus\ objects.
\end{description}
Additionally there are some convenience functions available. All of this will 
be described in more detail in this section.

\
Here, the structure of a \nexus\ tree is described by XML and then converted 
to \nexus\ by means of the \cpp{xml\_to\_nexus} function. The first argument 
of this function is the XML node while the second is the parent object 
below which the new structure should be created. All data already available 
in the XML file will be stored in the fields and attributes of the created
\nexus\-tree. 


%%%---------------------------------------------------------------------------
\subsubsection{XML from \nexus\ objects}\label{sec:xml:xmltonx}

The work horse for \nexus\ to XML conversion is the \cpp{nexus\_to\_xml} 
function template. The most probably simplest use case is demonstrated in the 
next example 
\begin{cppcode}
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>

using namespace pni::io::nx;

int main(int argc,char **argv)
{
    h5::nxfile f = ....;
    h5::nxgroup root = f.root();

    xml::node root_node;
    xml::nexus_to_xml(root,root_node);
    std::cout<<root_node<<std::endl;

    return 0;
}
\end{cppcode}
Here, the entire structure of the \nexus\ file is stored below the XML root 
node which is at the end dumped to standard output.
This simple example already raises an important question: how to deal with the
data stored in the \nexus\ file. As \nexus\ files can be used to store large 
amounts of data it would not be wise to convert all this data to ASCII (think 
about a 3D image stack stored in the file). However, some data might be 
required. 
The \cpp{nexus\_to\_xml} template thus provides a third optional argument which 
is a predicate function which decides for which field or attribute data will be
written to the file. 
The signature of the predicate is 
\begin{minted}[fontsize=\small]{cpp}
template<
         typename GTYPE,
         typename FTYPE,
         typename ATYPE
        >
bool predicate(const nxobject<GTYPE,FTYPE,ATYPE> &o);
\end{minted}
The function returns \cpp{true} if the data of a particular object should be 
included in the XML output. 
It is wise to not make this function to specific. Thus, the name of a field 
is not a good criterion for deciding whether or not to write data. A much 
better approach is to check for certain properties of an object. For the 
previous example a possible predicate could look like this
\begin{cppcode}
//code omitted 
bool write_scalars(const h5::nxobject &o)
{
    if(is_field(o) || is_attribute(o))
    {
       return size(o)==1;
    }
    else 
        return false;
}

int main(int argc,char **argv)
{
    //code omitted 
    xml::nexus_to_xml(root,root_node,write_scalars);

    //code omitted
    return 0;
}
\end{cppcode}
This predicate determines that only the data from fields and attributes 
is written to the XML tree if their size is equal to $1$ (in other words -- 
only scalars are written to the file). 
Such an approach keeps the resulting XML document small while using a rather 
general predicate which would match quite a lot of use cases. The default 
policy is to write no data.


%%%===========================================================================
\subsection{The XML low level interface}\label{sec:xml:lowlevel}

The entire XML stack in \libpniio\ is based upon the 
\cpp{boost::property\_tree} library. The \cpp{pni::io::nx::xml::ptree} type is 
nothing else than an alias to the \cpp{node} type provided by the 
\cpp{property\_tree} library.

%%%----------------------------------------------------------------------------
\subsubsection{Basic \cpp{node}-operations}

In order to simplify the work with \cpp{boost::property\_tree} \libpniio\ has
introduced some convenience functions. 
To create a new XML node one could use either 
\begin{cppcode}
xml::node = xml::create_from_string("....");
\end{cppcode}
or
\begin{cppcode}
xml::node = xml::create_from_file("filename.xml");
\end{cppcode}
The former function returns a node which refers to the root element of the 
XML structure provided by a string passed to the function as its only argument. 
The latter one reads the XML data from a file and returns a handle to its 
root element too.

\cpp{boost::property\_tree} uses nodes to store attributes of a tag which are 
accessible under a special name. To make accessing the attributes simpler 
there two functions.  
\begin{cppcode}
if(xml::has_attribute(field_node,"units"))
{
    xml::units_node = get_attribute(field_node,"units");

    // do something with the attribute
}
\end{cppcode}
\cpp{has\_attribute} returns true of a node possesses a particular attribute of
given name and \cpp{get\_attribute} returns a node instance referring to this 
attribute. 
The \cpp{xml::node} type and its related functions are provided by the
\cpp{xml/node.hpp} header file.

%%%----------------------------------------------------------------------------
\subsubsection{Utility classes}

There are two utility classes which should be described before we are dealing 
with the special classes for individual tasks. The two classes are 
\begin{description}
    \item[\cpp{data\_node}] a simple and special node which can be used to 
    retrieve data from a node. 
    \item[\cpp{io\_node}] the base class for the \cpp{attribute} and 
    \cpp{field} class.
\end{description}
The \cpp{data\_node} class provides only two static methods \cpp{read} and 
\cpp{write}. Both methods deal with the entire data content stored in a tag. 
To read the textual data stored in a tag one can simply use
\begin{cppcode}
xml::node n = ...;
string data = data_node::read(n);
\end{cppcode}
and to write 
\begin{cppcode}
xml::node n = ....;
string data = ....;
data_node::write(n,data);
\end{cppcode}
The \cpp{io\_node} class is used to access common properties of the 
\cpp{attribute} and \cpp{field} tag. The properties in common to 
attributes and fields are
\begin{itemize}
    \item data type
    \item number of dimensions (rank)
    \item number of elements along each dimension (shape)
    \item total number of elements stored in the tag (size).
\end{itemize}
The usage of the corresponding static methods is fairly simple 
\begin{cppcode}
xml::node n = ....;
auto shape = xml::io_node::shape<shape_t>(n);
size_t rank = xml::io_node::rank(n);
size_t size = xml::io_node::size(n);
std::cout<<"Type ID: "<<xml::io_node::type_id(n)<<std::endl;
\end{cppcode}
In addition to those methods there are two template methods which can be used 
to retrieve data from or to write data to the node. To read a single 
scalar value use
\begin{cppcode}
xml::node n = ...;
auto data = xml::io_node::data_from_xml<float64>(n);
\end{cppcode}
one can also use \cpp{std::vector} 
\begin{cppcode}
xml::node n = ...;
auto data = xml::io_node::data_from_xml<std::vector<float64>>(n);
\end{cppcode}


%%%----------------------------------------------------------------------------
\subsubsection{Handling tags}

Each tag in \libpniio's XML protocol is handled by an individual class and its
static methods. Each of these \emph{tag}-classes provides two major methods 
\cpp{object\_from\_xml} and \cpp{object\_to\_xml}. The former one creates a new
object of the tags type in memory while the latter one creates an XML
representation from a particular type.

%%%----------------------------------------------------------------------------
\subsubsection{The \cpp{dimensions} tag}

The \cpp{dimensions} tag provides information about the number of elements 
along each dimension of a multi-dimensional field or attribute. This tag is
handled by the \cpp{dimensions} class provided by \cpp{xml/dimensions.hpp}
header file. 
The \cpp{dimensions} class allows for inquiry of the \cpp{dimensions} tag 
within the XML structure. 
\begin{cppcode}
xml::node dims = .....;

std::cout<<"rank: "<<dimensions::rank(dims)<<std::endl;
std::cout<<"size: "<<dimensions::size(dims)<<std::endl;
\end{cppcode}
The \cpp{rank} member function returns the number of dimensions of the 
dimensions tag and the \cpp{size} method the total number of elements 
described by the \cpp{dimensions}-tag.

The memory representation of the \cpp{dimensions}-tag is a container 
whose elements are of type \cpp{size\_t} or any other compatible integer type. 
The default container is the \cpp{shape\_t} type provided by \libpnicore. 
To create an instance of \cpp{shape\_t} use
\begin{cppcode}
shape_t shape = dimensions::object_from_xml(dims);
\end{cppcode}
However, there is also a template version of \cpp{object\_from\_xml} 
\begin{cppcode}
typedef std::list<uint128> dim_type;
auto shape = dimensions::object_from_xml<dim_type>(dims);
\end{cppcode}
which can be used to store the number of elements in an arbitrary container.

The inverse operation, building a \cpp{dimensions}-tag from a container is 
implemented by the \cpp{object\_to\_xml} member function. 
\begin{cppcode}
shape_t shape{...};
xml::node dim_node = dimensions::object_to_xml(shape);
\end{cppcode}
This template member function accepts an arbitrary container with integer 
elements as its only argument and return a \cpp{xml::node} instance 
with the shape data.

%%%----------------------------------------------------------------------------
\subsubsection{The \cpp{attribute} tag}
The \cpp{attribute} tag is handled by a class of the same name which is 
a child class of \cpp{io\_node}. Aside from the inherited interface from 
\cpp{io\_node} the \cpp{attribute} class adds two additional static methods 
\begin{description}
    \item[\cpp{object\_from\_xml}] which generates an attribute from an 
    XML attribute tag
    \item[\cpp{object\_to\_xml}] which converts a \nexus\ attribute to 
    an XML tag.
\end{description}
It is important to note that this class deals only with attributes which 
are described by the attribute tag an not those which are part of the 
tag itself. 

%%%----------------------------------------------------------------------------
\subsubsection{The \cpp{group} tag}
The group tag is a simple container which can store either field or other group
tags. The group tag has two attributes: the name of the group and its
(base)class. At least the name of the group is mandatory and must be available
in any case. The base class is optional. If not provided, a non-\nexus\ group
without an \cpp{NX\_class} attribute will be created.

%%%----------------------------------------------------------------------------
\subsubsection{The \cpp{field} tag}
The \cpp{field} tag is handled by the \cpp{field} class which behaves pretty 
much as the \cpp{attribute} class. There is one major exception from the 
point of XML: fields do support compression. Currently only HDF5s deflate
compression is supported. To add compression use the \cpp{strategy} tag 
inside the \cpp{field} tag. The usage of the \cpp{strategy} tag is a 
remenesance from Jan Kotanskies \nexus\ data server. It might be replaced 
in future as more compression algorithms become available. 

%%%----------------------------------------------------------------------------
\subsubsection{The \cpp{link} tag}

The link tag indicates that the object that should be created is a link to
another object. Like the group tag it has only two attributes: the name of the
link within its parent group and the target to which the link should refer. 
The target can be either an object in the same file (internal link) or an object
in a different file (an external link). The \cpp{link} class which processes 
the information provided by the link tag has only an \cpp{object\_from\_xml} 
method as links are not indicated in XML output. 




