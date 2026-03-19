<!--

author:   DART Team
email:    dart@chop.edu
version:  1.4.1
current_version_description: Add text after Overview and Feedback that invites learners to the rest of the modules
language: en
narrator: UK English Female
title: Module Macros
comment:  This is placeholder module to save macros used in other modules.

@version_history 

Previous versions: 

- [1.3.0](https://liascript.github.io/course/?https://raw.githubusercontent.com/arcus/education_modules/bbd9189b6c598c77059da184995c83b4037cbd73/_module_templates/macros.md#1) :Add module\_id to macros for creating the REDCap survey link
- [1.2.1](https://liascript.github.io/course/?https://raw.githubusercontent.com/arcus/education_modules/a9aa1b38fc51db4252c9547654d9e36dba7864e5/_module_templates/macros.md#1): make CSS come from GCS
- [1.1.0](https://liascript.github.io/course/?https://raw.githubusercontent.com/arcus/education_modules/ad25398d0eef884402cff0f0c4fb4ca360d3b8f4/_module_templates/macros.md#1): Add current\_version\_description and version\_history metadata.

@end

@overview
<div class = "overview">

## Overview
@comment

**Is this module right for me?** @long_description

**Estimated time to completion:** @estimated_time_in_minutes minutes

**Pre-requisites**

@pre_reqs

**Learning Objectives**

After completion of this module, learners will be able to:

@learning_objectives

**Version History**

This version (@version): @current_version_description

@version_history

</div>

@end

icon: https://dscroft.github.io/liascript_materials/assets/logo.svg

link:  styles.css

script: https://kit.fontawesome.com/83b2343bd4.js
script:  https://code.jquery.com/jquery-3.6.0.slim.min.js

@hidecode
<script>
document.querySelectorAll('.lia-accordion__item').forEach((item) => {
    const h3 = item.querySelector('h3.lia-accordion__headline');
    if(h3 && h3.textContent.trim().toLowerCase() === @0) {
        item.style.display = 'none';
    }
});
</script>
@end

@headlesscode
<script>
document.querySelectorAll('.lia-accordion__item').forEach((item) => {
    const h3 = item.querySelector('h3.lia-accordion__headline');
    const label = item.querySelector('label.lia-accordion__header');
    
    if(label && h3 && h3.textContent.trim().toLowerCase() === @0) {
        label.style.display = 'none';
        return;
    }
});
</script>
@end
-->

# Module Macros

@overview

## Feedback

@feedback