using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Books.Models
{
    public class ContactInfo
    {
        [Key]
        public int ContactInfoId { get; set; }
        public string PhoneNumber { get; set; }

        //one-to-one relationship
        public virtual Publisher Publisher { get; set; }
    }
}